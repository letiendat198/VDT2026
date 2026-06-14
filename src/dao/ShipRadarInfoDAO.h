#ifndef SHIPRADARINFODAO_H
#define SHIPRADARINFODAO_H

#include "dao/BaseDAO.h"
#include "model/ShipRadarInfoModel.h"

class ShipRadarInfoDAO : public BaseDAO
{
public:
    ShipRadarInfoDAO();

    bool insert(ShipRadarInfoModel info);

    QList<ShipRadarInfoModel> getAllLastest();
    ShipRadarInfoModel getLastestByShipId(qint64 id);
    QList<ShipRadarInfoModel> getFromTimeByShipId(qint64 id, const QDateTime &timestamp);
};

#endif // SHIPRADARINFODAO_H
