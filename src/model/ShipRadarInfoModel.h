#ifndef SHIPRADARINFOMODEL_H
#define SHIPRADARINFOMODEL_H

#include <qtypes.h>
#include <QDateTime>

struct Coordinate {
    qreal latitude;
    qreal longitude;
};

class ShipRadarInfoModel
{
public:
    ShipRadarInfoModel();
    ShipRadarInfoModel(const Coordinate &coord, qreal angle, qreal speed, const QDateTime &timestamp);

    Coordinate coord() const;
    void setCoord(const Coordinate &newCoord);
    qreal angle() const;
    void setAngle(qreal newAngle);
    qreal speed() const;
    void setSpeed(qreal newSpeed);
    QDateTime timestamp() const;
    void setTimestamp(const QDateTime &newTimestamp);

private:
    Coordinate m_coord{};
    qreal m_angle{};
    qreal m_speed{};
    QDateTime m_timestamp{};
};

#endif // SHIPRADARINFOMODEL_H
