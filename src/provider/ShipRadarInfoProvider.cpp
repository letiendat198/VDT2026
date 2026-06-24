#include "ShipRadarInfoProvider.h"

ShipRadarInfoProvider::ShipRadarInfoProvider(QObject *parent) : QObject(parent), m_dao() {}

void ShipRadarInfoProvider::requestAllLatest() {
    // qDebug() << "Lastest radar info requested";
    // TODO: Make this async

    emit dataReady(m_dao.getAllLastest());
}
