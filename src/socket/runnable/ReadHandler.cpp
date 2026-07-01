#include "ReadHandler.h"
#include "model/ShipRadarInfoModel.h"

#include <QDataStream>
#include <QThread>

#include "provider/ShipRadarInfoProvider.h"

ReadHandler::ReadHandler(QPointer<QTcpSocket> socket) : m_socket(socket) {}

// Byte 0: Method. Not used, but just in case we want to expand later
// Byte 1-4: Size of message. May be overkill honestly
// Should be Big Edian
void ReadHandler::run() {
    QByteArray header = m_socket->read(5);
    QDataStream inHeader(header);

    quint8 method;
    quint32 size;
    inHeader >> method;
    inHeader >> size;

    // qDebug() << "Message method" << method;
    // qDebug() << "Message size" << size;

    QByteArray data = m_socket->read(size);
    QDataStream inData(data);

    // qDebug() << "Recv data body" << data.toHex();

    QList<ShipRadarInfoModel> listInfo;

    while (!inData.atEnd()) {
        ShipRadarInfoModel shipInfo;

        inData >> shipInfo;

        // qDebug() << shipInfo.shipId() << shipInfo.coord() << shipInfo.angle() << shipInfo.speed();

        listInfo.append(shipInfo);
    }

    ShipRadarInfoProvider::getInstance()->update(std::move(listInfo));
}
