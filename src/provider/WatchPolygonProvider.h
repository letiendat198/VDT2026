#ifndef WATCHPOLYGONPROVIDER_H
#define WATCHPOLYGONPROVIDER_H

#include <QObject>
#include <QQmlEngine>
#include <QList>
#include <QGeoCoordinate>

#include <model/WatchPolygonModel.h>

class WatchPolygonProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    WatchPolygonProvider(QObject *parent = nullptr);
    // TODO: Read and Write signature doesn't match, but this is more convenient on the QML side
    Q_INVOKABLE void requestAll();
    Q_INVOKABLE void add(QList<QGeoCoordinate> listCoord);

signals:
    void dataReady(QList<WatchPolygonModel>);
};

#endif // WATCHPOLYGONPROVIDER_H
