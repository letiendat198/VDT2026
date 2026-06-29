#include "WatchPolygonProvider.h"

WatchPolygonProvider::WatchPolygonProvider(QObject *parent) : QObject(parent), m_dao() {}

void WatchPolygonProvider::requestAll()
{
    // TODO: Make this async
    // qDebug() << "Requested data" << m_dao.getAll()[0].listCoord();

    emit dataReady(m_dao.getAll());
}

bool WatchPolygonProvider::add(QList<QGeoCoordinate> listCoord)
{
    // qDebug() << "Inserting a watch polygon";

    return m_dao.insert(WatchPolygonModel(listCoord));
}

bool WatchPolygonProvider::remove(int id)
{
    return m_dao.remove(id);
}
