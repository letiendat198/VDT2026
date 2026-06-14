#include "ReadHandler.h"
#include "dao/ShipRadarInfoDAO.h"
#include "model/ShipModel.h"

#include <QDataStream>

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

    QByteArray data = m_socket->read(size);
    QDataStream inData(data);

    ShipRadarInfoDAO shipInfoDAO;

    while (!inData.atEnd()) {
        ShipRadarInfoModel shipInfo;

        inData >> shipInfo;

        shipInfoDAO.insert(shipInfo);
    }
}
