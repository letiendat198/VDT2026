#include "ShipRadarInfoProvider.h"

#include <dao/ShipRadarInfoDAO.h>

ShipRadarInfoProvider::ShipRadarInfoProvider(QObject *parent) : QObject(parent) {}

void ShipRadarInfoProvider::requestAllLastest() {
    qDebug() << "Lastest radar info requested";

    ShipRadarInfoDAO shipInfoDAO;

    emit dataReady(shipInfoDAO.getAllLastest());
}
