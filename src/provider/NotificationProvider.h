#ifndef NOTIFICATIONPROVIDER_H
#define NOTIFICATIONPROVIDER_H

#include <QObject>
#include <QQmlEngine>
#include <QList>

#include "model/ShipRadarInfoModel.h"

class NotificationProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    NotificationProvider(QObject *parent = nullptr);

    void parseLiveData(QList<ShipRadarInfoModel> listShipInfo);
signals:
    void notificationReady(QString title, QString body);
};

#endif // NOTIFICATIONPROVIDER_H
