#include "ReadHandler.h"

ReadHandler::ReadHandler(QPointer<QTcpSocket> socket) : m_socket(socket) {}

void ReadHandler::run() {
    // m_socket->read();
}
