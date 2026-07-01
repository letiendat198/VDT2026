#include "ClientHandler.h"
#include "socket/runnable/ReadHandler.h"

#include <QThreadPool>

ClientHandler* ClientHandler::m_instance = nullptr;

ClientHandler::ClientHandler() : m_mapClient() {}

void ClientHandler::addClient(QTcpSocket *socket) {
    // Socket needs to be connected, otherwise there won't be port number
    Q_ASSERT(socket->state() == QAbstractSocket::ConnectedState);

    // TODO: Change this to actual unique identifier
    int clientPort = socket->peerPort();

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
    // qDebug() << "Client" << key << "have something to share";
    QPointer<QTcpSocket> client = m_mapClient[key];

    qDebug() << (QThread::currentThread() != this->thread() ? "readyRead slot called on another thread" : "readyRead slot called on main thread");

    if (!client) return;

    // Reading the socket from another thread makes this slot returns before data is actually read
    // Which will cause readyRead to be emitted recursively
    ReadHandler *readRunnable = new ReadHandler(client);
    QThreadPool::globalInstance()->start(readRunnable);
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