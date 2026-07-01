#include "ReadHandler.h"
#include "model/ShipRadarInfoModel.h"

#include <QDataStream>
#include <QThread>

#include "provider/ShipRadarInfoProvider.h"

ReadHandler::ReadHandler(QByteArray data) : m_data(data) {}

// Byte 0: Method. Not used, but just in case we want to expand later
// Byte 1-4: Size of message. May be overkill honestly
// Should be Big Edian
void ReadHandler::run() {
    QDataStream inData(m_data);

    // qDebug() << "Recv data body" << data.toHex();

    QList<ShipRadarInfoModel> listInfo;
    while (!inData.atEnd()) {
        ShipRadarInfoModel shipInfo;

        inData >> shipInfo;

        // qDebug() << "r" << shipInfo.shipId() << ":" << QDateTime::currentDateTime().toMSecsSinceEpoch();

        // qDebug() << shipInfo.shipId() << shipInfo.coord() << shipInfo.angle() << shipInfo.speed();

        listInfo.append(shipInfo);
    }

    ShipRadarInfoProvider::getInstance()->update(std::move(listInfo));
}
