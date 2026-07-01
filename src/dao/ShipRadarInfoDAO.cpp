#include "ShipRadarInfoDAO.h"
#include "utils/WKBConverter.h"

#include <QSqlQuery>

ShipRadarInfoDAO::ShipRadarInfoDAO() : BaseDAO() {}

ShipRadarInfoDAO::ShipRadarInfoDAO(const QString &key) : BaseDAO(key) {}

bool ShipRadarInfoDAO::insert(ShipRadarInfoModel info) {
    QSqlQuery query(m_db);

    bool ok = query.prepare("INSERT INTO ship_radar_info (coordinate, speed, angle, timestamp, ship_id) VALUES(?, ?, ?, ?, ?);");
    if (!ok) qDebug() << query.lastError();

    // https://postgis.net/documentation/tips/lon-lat-or-lat-lon/
    query.addBindValue(QString("SRID=4326;POINT(%1 %2)").arg(info.coord().longitude()).arg(info.coord().latitude()));
    // query.addBindValue(QString::number(info.coord().longitude()));
    // query.addBindValue(QString::number(info.coord().latitude()));
    query.addBindValue(info.speed());
    query.addBindValue(info.angle());
    query.addBindValue(info.timestamp());
    query.addBindValue(info.shipId());

    ok = query.exec();
    if (!ok) qDebug() << query.lastError();

    return ok;
}

bool ShipRadarInfoDAO::insertMany(QList<ShipRadarInfoModel> listInfo)
{
    bool ok = m_db.transaction();
    if (!ok) return false;

    Q_FOREACH(ShipRadarInfoModel model, listInfo) {
        ok = insert(model);
        if (!ok) {
            m_db.rollback();
            return false;
        }
    }

    m_db.commit();
    return true;
}

QList<ShipRadarInfoModel> ShipRadarInfoDAO::getAllLastest() {
    QSqlQuery query(m_db);

    // Id is auto incrementing, max id should be lastest
    // Ship id should be unique too!
    bool ok = query.prepare("SELECT ST_AsBinary(coordinate), speed, angle, timestamp, ship_id, watch_polygon.id "
                  "FROM ship_radar_info "
                  "LEFT JOIN watch_polygon ON ST_COVERS(watch_polygon.polygon, ship_radar_info.coordinate) "
                  "WHERE ship_radar_info.id IN (SELECT MAX(ship_radar_info.id) FROM ship_radar_info GROUP BY ship_id);");
    if (!ok) qDebug() << query.lastError();

    ok = query.exec();
    if (!ok) qDebug() << query.lastError();

    QHash<qint64, ShipRadarInfoModel> mapModel;

    while (query.next()) {
        qint64 shipId = query.value(4).toLongLong();
        QVariant watchPolygonIdValue = query.value(5);
        bool crossesWatchPolygon = watchPolygonIdValue.isValid() == true && watchPolygonIdValue.isNull() == false;

        // JOIN can produce duplicates (because one ship can belongs to many watch polygons)
        // So check if existed, if yes then just add watch polygon id to existing list
        if (mapModel.contains(shipId)) {
            if (!crossesWatchPolygon) continue;

            int watchPolygonId = watchPolygonIdValue.toInt();
            mapModel[shipId].addCrossedWatchPolygon(watchPolygonId);
        }
        else {
            QGeoCoordinate coord = WKBConverter(query.value(0).toByteArray()).toCoord();
            qreal speed = query.value(1).toReal();
            qreal angle = query.value(2).toReal();
            QDateTime timestamp = query.value(3).toDateTime();

            ShipRadarInfoModel model;
            model.setShipId(shipId);
            model.setCoord(coord);
            model.setSpeed(speed);
            model.setAngle(angle);
            model.setTimestamp(timestamp);
            if (crossesWatchPolygon) {
                int watchPolygonId = watchPolygonIdValue.toInt();
                model.addCrossedWatchPolygon(watchPolygonId);
            }

            mapModel[shipId] = model;
        }
    }

    return mapModel.values();
}

QList<ShipRadarInfoModel> ShipRadarInfoDAO::getAllLatestWatchOnly()
{
    QSqlQuery query(m_db);

    // Id is auto incrementing, max id should be lastest
    // Ship id should be unique too!
    bool ok = query.prepare("SELECT ship_id, watch_polygon.id "
                            "FROM ship_radar_info "
                            "LEFT JOIN watch_polygon ON ST_COVERS(watch_polygon.polygon, ship_radar_info.coordinate) "
                            "WHERE ship_radar_info.id IN (SELECT MAX(ship_radar_info.id) FROM ship_radar_info GROUP BY ship_id);");
    if (!ok) qDebug() << query.lastError();

    ok = query.exec();
    if (!ok) qDebug() << query.lastError();

    QHash<qint64, ShipRadarInfoModel> mapModel;

    while (query.next()) {
        qint64 shipId = query.value(0).toLongLong();
        QVariant watchPolygonIdValue = query.value(1);
        bool crossesWatchPolygon = watchPolygonIdValue.isValid() == true && watchPolygonIdValue.isNull() == false;

        // JOIN can produce duplicates (because one ship can belongs to many watch polygons)
        // So check if existed, if yes then just add watch polygon id to existing list
        if (mapModel.contains(shipId)) {
            if (!crossesWatchPolygon) continue;

            int watchPolygonId = watchPolygonIdValue.toInt();
            mapModel[shipId].addCrossedWatchPolygon(watchPolygonId);
        }
        else {
            ShipRadarInfoModel model;
            model.setShipId(shipId);
            if (crossesWatchPolygon) {
                int watchPolygonId = watchPolygonIdValue.toInt();
                model.addCrossedWatchPolygon(watchPolygonId);
            }

            mapModel[shipId] = model;
        }
    }

    return mapModel.values();
}

ShipRadarInfoModel ShipRadarInfoDAO::getLastestByShipId(qint64 id) {
    QSqlQuery query(m_db);

    query.prepare("SELECT ST_AsBinary(coordinate), speed, angle, timestamp FROM ship_radar_info WHERE ship_id = ? ORDER BY timestamp DESC LIMIT 1;");

    query.addBindValue(id);
    query.exec();

    ShipRadarInfoModel model;

    while (query.next()) {
        model.setShipId(id);
        model.setCoord(WKBConverter(query.value(0).toByteArray()).toCoord());
        model.setSpeed(query.value(1).toReal());
        model.setAngle(query.value(2).toReal());
        model.setTimestamp(query.value(3).toDateTime());
    }

    return model;
}

QList<ShipRadarInfoModel> ShipRadarInfoDAO::getFromTimeByShipId(qint64 id, const QDateTime &timestamp) {
    QSqlQuery query(m_db);

    query.prepare("SELECT ST_AsBinary(coordinate), speed, angle, timestamp FROM ship_radar_info WHERE ship_id = ? AND timestamp > ?;");

    query.addBindValue(id);
    // TODO: This may not include milisecond, which we need. So watch out? Probably need to format to string!
    query.addBindValue(timestamp);
    query.exec();

    QList<ShipRadarInfoModel> listModel;

    while (query.next()) {
        ShipRadarInfoModel model;
        model.setShipId(id);
        model.setCoord(WKBConverter(query.value(0).toByteArray()).toCoord());
        model.setSpeed(query.value(1).toReal());
        model.setAngle(query.value(2).toReal());
        model.setTimestamp(query.value(3).toDateTime());

        listModel.append(model);
    }

    return listModel;
}
