#ifndef WATCHPOLYGONMODEL_H
#define WATCHPOLYGONMODEL_H

#include <QObject>
#include <qqmlintegration.h>
#include <QGeoCoordinate>

class WatchPolygonModel
{
    Q_GADGET // Use Q_GADGET cause QObject would be overkill. We don't need signals here anyways
    QML_VALUE_TYPE(watchPolygon)
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QList<QGeoCoordinate> listCoord READ listCoord)
public:
    WatchPolygonModel();
    WatchPolygonModel(int id, const QList<QGeoCoordinate> &listCoord);
    WatchPolygonModel(const QList<QGeoCoordinate> &listCoord);

    int id() const;
    void setId(int newId);
    QList<QGeoCoordinate> listCoord() const;
    void setListCoord(const QList<QGeoCoordinate> &newListCoord);

    QString toWKT();

private:
    int m_id{};
    QList<QGeoCoordinate> m_listCoord{};
};

#endif //WATCHPOLYGONMODEL_H
