#include "WatchPolygonDAO.h"

#include <QSqlQuery>

#include <utils/WKBConverter.h>

WatchPolygonDAO::WatchPolygonDAO() : BaseDAO() {}

WatchPolygonDAO::WatchPolygonDAO(const QString &key) : BaseDAO(key) {}

bool WatchPolygonDAO::insert(WatchPolygonModel model) {
    QSqlQuery query(m_db);

    bool ok = query.prepare("INSERT INTO watch_polygon (polygon) VALUES(?);");
    if (!ok) qDebug() << query.lastError();

    query.addBindValue(model.toWKT());

    ok = query.exec();
    if (!ok) qDebug() << query.lastError();

    return ok;
}

QList<WatchPolygonModel> WatchPolygonDAO::getAll() {
    QSqlQuery query(m_db);

    query.prepare("SELECT id, ST_AsBinary(polygon) FROM watch_polygon;");
    query.exec();

    QList<WatchPolygonModel> listModel;

    while (query.next()) {
        WatchPolygonModel model;
        model.setId(query.value(0).toInt());
        model.setListCoord(WKBConverter(query.value(1).toByteArray()).toListCoord());

        listModel.append(model);
    }

    return listModel;
}

bool WatchPolygonDAO::remove(int id)
{
    QSqlQuery query(m_db);

    bool ok = query.prepare("DELETE FROM watch_polygon WHERE id = ?;");
    if (!ok) qDebug() << query.lastError();

    query.addBindValue(id);

    ok = query.exec();
    if (!ok) qDebug() << query.lastError();

    return ok;
}
