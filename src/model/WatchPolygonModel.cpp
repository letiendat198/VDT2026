#include "WatchPolygonModel.h"
#include "QDebug"

WatchPolygonModel::WatchPolygonModel() {}

WatchPolygonModel::WatchPolygonModel(int id, const QList<QGeoCoordinate> &listCoord) : m_id(id),
    m_listCoord(listCoord)
{}

WatchPolygonModel::WatchPolygonModel(const QList<QGeoCoordinate> &listCoord) : m_listCoord(listCoord) {}

int WatchPolygonModel::id() const
{
    return m_id;
}

void WatchPolygonModel::setId(int newId)
{
    m_id = newId;
}

QList<QGeoCoordinate> WatchPolygonModel::listCoord() const
{
    return m_listCoord;
}

void WatchPolygonModel::setListCoord(const QList<QGeoCoordinate> &newListCoord)
{
    m_listCoord = newListCoord;
}

QString WatchPolygonModel::toWKT()
{
    // long first, lat later
    QString wkt = QString("SRID=4326;POLYGON((");

    Q_FOREACH(QGeoCoordinate coord, m_listCoord) {
        wkt.append(QString("%1 %2, ").arg(coord.longitude()).arg(coord.latitude()));
    }

    wkt.append(QString("%1 %2))").arg(m_listCoord[0].longitude()).arg(m_listCoord[0].latitude())); // Polygon consists of LinearRing. LinearRing start and end must be equal

    qDebug() << wkt;

    return std::move(wkt);
}
