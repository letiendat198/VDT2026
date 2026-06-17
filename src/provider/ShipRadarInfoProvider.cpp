#include "ShipRadarInfoProvider.h"

#include <dao/ShipRadarInfoDAO.h>

ShipRadarInfoProvider::ShipRadarInfoProvider(QObject *parent) : QObject(parent) {}

void ShipRadarInfoProvider::requestAllLatest() {
    // qDebug() << "Lastest radar info requested";

    ShipRadarInfoDAO shipInfoDAO;

    emit dataReady(shipInfoDAO.getAllLastest());
}
