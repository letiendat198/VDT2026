#include "ClientHandler.h"

ClientHandler* ClientHandler::m_instance = nullptr;

ClientHandler::ClientHandler() : m_mapClient() {}

void ClientHandler::addClient(QTcpSocket *socket) {
    // Socket needs to be connected, otherwise there won't be port number
    Q_ASSERT(socket->state() == QAbstractSocket::ConnectedState);

    int clientPort = socket->localPort();

    connect(socket, &QTcpSocket::disconnected, this, [this, clientPort](){
        onClientDisconnected(clientPort);
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [this, clientPort](QAbstractSocket::SocketError error){
        onClientError(clientPort, error);
    });

    connect(socket, &QTcpSocket::readyRead, this, [this, clientPort](){
        onClientIncoming(clientPort);
    });

    m_mapClient.insert(clientPort, QPointer(socket));
}

void ClientHandler::onClientIncoming(int key) {
    QPointer<QTcpSocket> client = m_mapClient[key];

    if (!client) return;


}

void ClientHandler::onClientDisconnected(int key) {
    QPointer<QTcpSocket> client = m_mapClient.take(key);

    if (!client) {
        qDebug() << "Disconnected client somehow does not exist in map";
        return;
    }

    // QTcpSocket is a child of QTcpServer, so it exists as long as socket server exists
    // Delete it explicitly
    client->deleteLater();
}

void ClientHandler::onClientError(int key, QAbstractSocket::SocketError error) {
    qDebug() << error;

    onClientDisconnected(key);
}