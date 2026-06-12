#ifndef SHIPRADARINFODAO_H
#define SHIPRADARINFODAO_H

#include "dao/BaseDAO.h"
#include "model/ShipRadarInfoModel.h"

class ShipRadarInfoDAO : public BaseDAO
{
public:
    ShipRadarInfoDAO();

    bool insertByShipId(const QString &id, ShipRadarInfoModel info);

    ShipRadarInfoModel getLastestByShipId(const QString &id);
    QList<ShipRadarInfoModel> getFromTimeByShipId(const QString &id, const QDateTime &timestamp);
};

#endif // SHIPRADARINFODAO_H
