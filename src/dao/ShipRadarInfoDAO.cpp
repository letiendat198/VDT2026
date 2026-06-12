#include "ShipRadarInfoDAO.h"
#include "utils/WKBConverter.h"

#include <QSqlQuery>

ShipRadarInfoDAO::ShipRadarInfoDAO() {}

bool ShipRadarInfoDAO::insertByShipId(const QString &id, ShipRadarInfoModel info) {
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO ship_radar_info (coordinate, speed, angle, timestamp, ship_id) VALUES('SRID=4326;POINT(?, ?)', ?, ?, ?, ?) ");

    // https://postgis.net/documentation/tips/lon-lat-or-lat-lon/
    query.addBindValue(info.coord().longitude);
    query.addBindValue(info.coord().latitude);
    query.addBindValue(info.speed());
    query.addBindValue(info.angle());
    query.addBindValue(info.timestamp());
    query.addBindValue(id);

    return query.exec();
}

ShipRadarInfoModel ShipRadarInfoDAO::getLastestByShipId(const QString &id) {
    QSqlQuery query(m_db);

    query.prepare("SELECT ST_AsBinary(coordinate), speed, angle, timestamp FROM ship_radar_info WHERE ship_id = ? ORDER BY timestamp DESC LIMIT 1");

    query.addBindValue(id);

    ShipRadarInfoModel model;

    while (query.next()) {
        model.setCoord(WKBConverter(query.value(0).toString()).toCoord());
        model.setSpeed(query.value(1).toReal());
        model.setAngle(query.value(2).toReal());
        model.setTimestamp(query.value(3).toDateTime());
    }

    return model;
}

QList<ShipRadarInfoModel> ShipRadarInfoDAO::getFromTimeByShipId(const QString &id, const QDateTime &timestamp) {
    QSqlQuery query(m_db);

    query.prepare("SELECT ST_AsBinary(coordinate), speed, angle, timestamp FROM ship_radar_info WHERE ship_id = ? AND timestamp > ?");

    query.addBindValue(id);
    // TODO: This may not include milisecond, which we need. So watch out? Probably need to format to string!
    query.addBindValue(timestamp);

    QList<ShipRadarInfoModel> listModel;

    while (query.next()) {
        ShipRadarInfoModel model;
        model.setCoord(WKBConverter(query.value(0).toString()).toCoord());
        model.setSpeed(query.value(1).toReal());
        model.setAngle(query.value(2).toReal());
        model.setTimestamp(query.value(3).toDateTime());

        listModel.append(model);
    }

    return listModel;
}
