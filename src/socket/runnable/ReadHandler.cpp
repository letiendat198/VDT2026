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
    if (m_socket->isTransactionStarted()) {
        qDebug() << "Socket is being processed by another thread";
        return;
    }
    m_socket->startTransaction();

    QByteArray header = m_socket->read(5);
    if (header.size() < 5) {
        qDebug() << "Not enough data for header, return";
        m_socket->rollbackTransaction();
        return;
    }

    QDataStream inHeader(header);

    quint8 method;
    quint32 size;
    inHeader >> method;
    inHeader >> size;

    qDebug() << "Message method" << method;
    qDebug() << "Message size" << size;

    QByteArray data = m_socket->read(size);
    qDebug() << "Read" << data.size();
    while (data.size() < size) {
        qDebug() << "Missing" << size - data.size() << "bytes";
        QByteArray missing = m_socket->read(size - data.size());
        data.append(missing);
    }
    QDataStream inData(data);

    // qDebug() << "Recv data body" << data.toHex();

    QList<ShipRadarInfoModel> listInfo;

    // qDebug() << "Reading from socket" << m_socket->peerPort();

    while (!inData.atEnd()) {
        ShipRadarInfoModel shipInfo;

        inData >> shipInfo;

        // qDebug() << "r" << shipInfo.shipId() << ":" << QDateTime::currentDateTime().toMSecsSinceEpoch();

        // qDebug() << shipInfo.shipId() << shipInfo.coord() << shipInfo.angle() << shipInfo.speed();

        listInfo.append(shipInfo);
    }

    ShipRadarInfoProvider::getInstance()->update(std::move(listInfo));

    // qDebug() << "Finished writing to Db in socket" << m_socket->peerPort();

    m_socket->commitTransaction();
}
