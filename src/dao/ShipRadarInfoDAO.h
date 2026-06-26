#ifndef SHIPRADARINFODAO_H
#define SHIPRADARINFODAO_H

#include "dao/BaseDAO.h"
#include "model/ShipRadarInfoModel.h"

class ShipRadarInfoDAO : public BaseDAO
{
public:
    ShipRadarInfoDAO();
    ShipRadarInfoDAO(const QString &key);

    bool insert(ShipRadarInfoModel info);
    bool insertMany(QList<ShipRadarInfoModel> listInfo);

    QList<ShipRadarInfoModel> getAllLastest();
    // Same as getAllLastest(), but only within region. For lazy-loading
    QList<ShipRadarInfoModel> getAllLastestWithin(const QList<QGeoCoordinate> &polygon);
    ShipRadarInfoModel getLastestByShipId(qint64 id);
    QList<ShipRadarInfoModel> getFromTimeByShipId(qint64 id, const QDateTime &timestamp);
};

#endif // SHIPRADARINFODAO_H
