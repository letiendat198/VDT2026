#ifndef SHIPRADARINFOPROVIDER_H
#define SHIPRADARINFOPROVIDER_H

#include <QObject>
#include <QQmlEngine>
#include <QList>

#include <model/ShipRadarInfoModel.h>
#include <dao/ShipRadarInfoDAO.h>

class ShipRadarInfoProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    ShipRadarInfoProvider(QObject *parent = nullptr);
    Q_INVOKABLE void requestAllLatest();
    Q_INVOKABLE void requestAllLatestWithin(const QList<QGeoCoordinate> &polygon);

signals:
    void dataReady(QList<ShipRadarInfoModel>);
};

#endif // SHIPRADARINFOPROVIDER_H
