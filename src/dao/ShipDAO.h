#ifndef SHIPDAO_H
#define SHIPDAO_H

#include "dao/BaseDAO.h"
#include "model/ShipModel.h"

class ShipDAO : public BaseDAO
{
public:
    ShipDAO();

    bool insert(ShipModel ship);
    bool insert(QList<ShipModel> listShip);

    ShipModel getLastestInfoById(const QString &id);
    ShipModel getAllInfoById(const QString &id);
};

#endif // SHIPDAO_H
