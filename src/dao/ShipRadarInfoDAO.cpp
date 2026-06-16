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
    query.prepare("SELECT ST_AsBinary(coordinate), speed, angle, timestamp, ship_id "
                  "FROM ship_radar_info WHERE id IN (SELECT MAX(id) FROM ship_radar_info GROUP BY ship_id);");

    query.exec();

    QList<ShipRadarInfoModel> listModel;

    while (query.next()) {
        ShipRadarInfoModel model;
        model.setShipId(query.value(4).toLongLong());
        model.setCoord(WKBConverter(query.value(0).toByteArray()).toCoord());
        model.setSpeed(query.value(1).toReal());
        model.setAngle(query.value(2).toReal());
        model.setTimestamp(query.value(3).toDateTime());

        listModel.append(model);
    }

    return listModel;
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
