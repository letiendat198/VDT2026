#include "ReadHandler.h"
#include "dao/ShipRadarInfoDAO.h"
#include "model/ShipRadarInfoModel.h"

#include <QDataStream>
#include <QThread>

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

    // Since we can't use QThread::currentThreadId() because Qt warned against using it
    // Next best thing is probably thread addr. Hope it doesn't get reallocated...
    // But, if it does, shouldn't it considered a new thread anyways
    quintptr threadAddr = reinterpret_cast<quintptr>(QThread::currentThread());

    ShipRadarInfoDAO shipInfoDAO(QString::number(threadAddr));
    QList<ShipRadarInfoModel> listInfo;

    while (!inData.atEnd()) {
        ShipRadarInfoModel shipInfo;

        inData >> shipInfo;

        // qDebug() << shipInfo.shipId() << shipInfo.coord() << shipInfo.angle() << shipInfo.speed();

        listInfo.append(shipInfo);
    }

    shipInfoDAO.insertMany(listInfo);
}
