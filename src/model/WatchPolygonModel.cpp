#include "WatchPolygonModel.h"

WatchPolygonModel::WatchPolygonModel() {}

WatchPolygonModel::WatchPolygonModel(int id, const QPolygonF &polygon) : m_id(id),
    m_polygon(polygon)
{}

int WatchPolygonModel::id() const
{
    return m_id;
}

void WatchPolygonModel::setId(int newId)
{
    m_id = newId;
}

QPolygonF WatchPolygonModel::polygon() const
{
    return m_polygon;
}

void WatchPolygonModel::setPolygon(const QPolygonF &newPolygon)
{
    m_polygon = newPolygon;
}

QString WatchPolygonModel::toWKT()
{
    QString wkt = QString("SRID=4326;POLYGON((");

    Q_FOREACH(QPointF point, m_polygon.toList()) {
        wkt.append("%1 %2, ");
    }

    wkt.removeLast();
    wkt.removeLast();

    wkt.append("))");

    return std::move(wkt);
}



