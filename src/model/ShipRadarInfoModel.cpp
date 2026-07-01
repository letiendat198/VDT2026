#include "ShipRadarInfoModel.h"

ShipRadarInfoModel::ShipRadarInfoModel() {

}

ShipRadarInfoModel::ShipRadarInfoModel(qint64 shipId, const QGeoCoordinate &coord, qreal angle, qreal speed, const QDateTime &timestamp)
    : m_shipId(shipId),
    m_coord(coord),
    m_angle(std::move(angle)),
    m_speed(std::move(speed)),
    m_timestamp(timestamp),
    m_listCrossedWatchPolygonId()
{}

QGeoCoordinate ShipRadarInfoModel::coord() const
{
    return m_coord;
}

void ShipRadarInfoModel::setCoord(const QGeoCoordinate &newCoord)
{
    m_coord = newCoord;
}

qreal ShipRadarInfoModel::angle() const
{
    return m_angle;
}

void ShipRadarInfoModel::setAngle(qreal newAngle)
{
    m_angle = newAngle;
}

qreal ShipRadarInfoModel::speed() const
{
    return m_speed;
}

void ShipRadarInfoModel::setSpeed(qreal newSpeed)
{
    m_speed = newSpeed;
}

QDateTime ShipRadarInfoModel::timestamp() const
{
    return m_timestamp;
}

void ShipRadarInfoModel::setTimestamp(const QDateTime &newTimestamp)
{
    m_timestamp = newTimestamp;
}

qint64 ShipRadarInfoModel::shipId() const
{
    return m_shipId;
}

void ShipRadarInfoModel::setShipId(qint64 newShipId)
{
    m_shipId = newShipId;
}

QList<int> ShipRadarInfoModel::listCrossedWatchPolygonId() const
{
    return m_listCrossedWatchPolygonId;
}

void ShipRadarInfoModel::setListCrossedWatchPolygonId(const QList<int> &newList)
{
    m_listCrossedWatchPolygonId = newList;
}

void ShipRadarInfoModel::addCrossedWatchPolygon(int id)
{
    m_listCrossedWatchPolygonId.append(id);
}

void ShipRadarInfoModel::copyExceptCrossedWatchPolygon(const ShipRadarInfoModel &ship)
{
    setShipId(ship.shipId());
    setCoord(ship.coord());
    setAngle(ship.angle());
    setSpeed(ship.speed());
    setTimestamp(ship.timestamp());
}

QDataStream &operator<<(QDataStream &stream, const ShipRadarInfoModel &shipInfo) {
    stream << shipInfo.shipId();
    stream << shipInfo.coord().latitude();
    stream << shipInfo.coord().longitude();
    stream << shipInfo.angle();
    stream << shipInfo.speed();
    // Undocumented. IDK how Qt serialize this QDateTime
    // stream << shipInfo.timestamp();
    // Use epoch MS for easier time serializing
    stream << shipInfo.timestamp().toMSecsSinceEpoch();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, ShipRadarInfoModel &shipInfo) {
    qint64 shipId;
    qreal lat;
    qreal log;
    qreal angle;
    qreal speed;
    quint64 epochMs;

    stream >> shipId;
    stream >> lat;
    stream >> log;
    stream >> angle;
    stream >> speed;
    stream >> epochMs;

    QDateTime timestamp = QDateTime::fromMSecsSinceEpoch(epochMs);

    shipInfo = ShipRadarInfoModel(shipId, QGeoCoordinate(lat, log), angle, speed, timestamp);

    return stream;
}
