#include "ShipRadarInfoModel.h"

ShipRadarInfoModel::ShipRadarInfoModel() {

}

ShipRadarInfoModel::ShipRadarInfoModel(const Coordinate &coord, qreal angle, qreal speed, const QDateTime &timestamp) : m_coord(coord),
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
