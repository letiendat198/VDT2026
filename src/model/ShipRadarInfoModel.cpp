#include "ShipRadarInfoModel.h"

ShipRadarInfoModel::ShipRadarInfoModel() {

}

ShipRadarInfoModel::ShipRadarInfoModel(qint64 shipId, const Coordinate &coord, qreal angle, qreal speed, const QDateTime &timestamp)
    : m_shipId(shipId),
    m_coord(coord),
    m_angle(std::move(angle)),
    m_speed(std::move(speed)),
    m_timestamp(timestamp)
{}

Coordinate ShipRadarInfoModel::coord() const
{
    return m_coord;
}

void ShipRadarInfoModel::setCoord(const Coordinate &newCoord)
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

QDataStream &operator<<(QDataStream &stream, const ShipRadarInfoModel &shipInfo) {
    stream << shipInfo.shipId();
    stream << shipInfo.coord().latitude;
    stream << shipInfo.coord().longitude;
    stream << shipInfo.angle();
    stream << shipInfo.speed();
    stream << shipInfo.timestamp();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, ShipRadarInfoModel &shipInfo) {
    qint64 shipId;
    Coordinate coord;
    qreal angle;
    qreal speed;
    QDateTime timestamp;

    stream >> shipId;
    stream >> coord.latitude;
    stream >> coord.longitude;
    stream >> angle;
    stream >> speed;
    stream >> timestamp;

    shipInfo = ShipRadarInfoModel(shipId, coord, angle, speed, timestamp);

    return stream;
}
