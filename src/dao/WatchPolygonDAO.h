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
};

#endif // WATCHPOLYGONDAO_H
