#ifndef WATCHPOLYGONMODEL_H
#define WATCHPOLYGONMODEL_H

#include <QPolygon>
#include <QObject>
#include <qqmlintegration.h>

class WatchPolygonModel
{
    // Q_GADGET // Use Q_GADGET cause QObject would be overkill. We don't need signals here anyways
    // QML_VALUE_TYPE(watchPolygon)
    // Q_PROPERTY(int id READ id)
    // Q_PROPERTY(QPolygon polygon READ polygon)
public:
    WatchPolygonModel();
    WatchPolygonModel(int id, const QPolygonF &polygon);

    int id() const;
    void setId(int newId);
    QPolygonF polygon() const;
    void setPolygon(const QPolygonF &newPolygon);

    QString toWKT();

private:
    int m_id;
    QPolygonF m_polygon;
};

#endif //WATCHPOLYGONMODEL_H
