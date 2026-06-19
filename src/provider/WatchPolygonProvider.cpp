#include "WatchPolygonProvider.h"
#include "dao/WatchPolygonDAO.h"


WatchPolygonProvider::WatchPolygonProvider(QObject *parent) : QObject(parent) {}

void WatchPolygonProvider::requestAll()
{
    // TODO: Make this async
    WatchPolygonDAO dao;

    qDebug() << "Requested data" << dao.getAll()[0].listCoord();

    emit dataReady(dao.getAll());
}

void WatchPolygonProvider::add(QList<QGeoCoordinate> listCoord)
{
    qDebug() << "Inserting a watch polygon";

    WatchPolygonDAO dao;

    dao.insert(WatchPolygonModel(listCoord));
}
