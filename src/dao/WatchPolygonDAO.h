#ifndef WATCHPOLYGONDAO_H
#define WATCHPOLYGONDAO_H

#include "dao/BaseDAO.h"
#include "model/WatchPolygonModel.h"

class WatchPolygonDAO : public BaseDAO
{
public:
    WatchPolygonDAO();
    WatchPolygonDAO(const QString &key);

    bool insert(WatchPolygonModel info);
    QList<WatchPolygonModel> getAll();
    bool remove(int id);
};

#endif // WATCHPOLYGONDAO_H
