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

signals:
    void dataReady(QList<ShipRadarInfoModel>);

private:
    ShipRadarInfoDAO m_dao{};
};

#endif // SHIPRADARINFOPROVIDER_H
