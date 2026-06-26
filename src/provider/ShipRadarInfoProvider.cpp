#include "ShipRadarInfoProvider.h"

#include <QThreadPool>

ShipRadarInfoProvider::ShipRadarInfoProvider(QObject *parent) : QObject(parent) {}

void ShipRadarInfoProvider::requestAllLatest() {
    // qDebug() << "Lastest radar info requested";
    // TODO: Make this async

    QThreadPool::globalInstance()->start([this]() {
        quintptr threadAddr = reinterpret_cast<quintptr>(QThread::currentThread());
        ShipRadarInfoDAO dao = ShipRadarInfoDAO(QString::number(threadAddr));
        QList<ShipRadarInfoModel> data = dao.getAllLastest();
        emit dataReady(data);
    });
}
