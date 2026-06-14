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
    ShipRadarInfoModel(qint64 shipId, const Coordinate &coord, qreal angle, qreal speed, const QDateTime &timestamp);

    Coordinate coord() const;
    void setCoord(const Coordinate &newCoord);
    qreal angle() const;
    void setAngle(qreal newAngle);
    qreal speed() const;
    void setSpeed(qreal newSpeed);
    QDateTime timestamp() const;
    void setTimestamp(const QDateTime &newTimestamp);
    qint64 shipId() const;
    void setShipId(qint64 newShipId);

private:
    qint64 m_shipId{};
    Coordinate m_coord{};
    qreal m_angle{};
    qreal m_speed{};
    QDateTime m_timestamp{};
};

QDataStream &operator<<(QDataStream &stream, const ShipRadarInfoModel &shipInfo);
QDataStream &operator>>(QDataStream &stream, ShipRadarInfoModel &shipInfo);

#endif // SHIPRADARINFOMODEL_H
