#ifndef SHIPRADARINFOMODEL_H
#define SHIPRADARINFOMODEL_H

#include <QObject>
#include <qqmlintegration.h>
#include <qtypes.h>
#include <QDateTime>
#include <QGeoCoordinate>

class ShipRadarInfoModel
{
    Q_GADGET // Use Q_GADGET cause QObject would be overkill. We don't need signals here anyways
    QML_VALUE_TYPE(shipRadarInfo)
    Q_PROPERTY(QGeoCoordinate coord READ coord)
    Q_PROPERTY(qreal angle READ angle)
    Q_PROPERTY(qreal speed READ speed)
    Q_PROPERTY(QDateTime timestamp READ timestamp)
    Q_PROPERTY(qint64 shipId READ shipId)
    Q_PROPERTY(QList<int> listCrossedWatchPolygonId READ listCrossedWatchPolygonId)

public:
    ShipRadarInfoModel();
    ShipRadarInfoModel(qint64 shipId, const QGeoCoordinate &coord, qreal angle, qreal speed, const QDateTime &timestamp);

    QGeoCoordinate coord() const;
    void setCoord(const QGeoCoordinate &newCoord);
    qreal angle() const;
    void setAngle(qreal newAngle);
    qreal speed() const;
    void setSpeed(qreal newSpeed);
    QDateTime timestamp() const;
    void setTimestamp(const QDateTime &newTimestamp);
    qint64 shipId() const;
    void setShipId(qint64 newShipId);

    QList<int> listCrossedWatchPolygonId() const;
    void addCrossedWatchPolygon(int id);

private:
    qint64 m_shipId{};
    QGeoCoordinate m_coord{};
    qreal m_angle{};
    qreal m_speed{};
    QDateTime m_timestamp{};
    QList<int> m_listCrossedWatchPolygonId{};
};

QDataStream &operator<<(QDataStream &stream, const ShipRadarInfoModel &shipInfo);
QDataStream &operator>>(QDataStream &stream, ShipRadarInfoModel &shipInfo);

#endif // SHIPRADARINFOMODEL_H
