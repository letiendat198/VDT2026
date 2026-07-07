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
    QString clientAddr = socket->peerAddress().toString();
    QString key = clientAddr + ":" + QString::number(clientPort);

    connect(socket, &QTcpSocket::disconnected, this, [this, key](){
        onClientDisconnected(key);
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [this, key](QAbstractSocket::SocketError error){
        onClientError(key, error);
    });

    connect(socket, &QTcpSocket::readyRead, this, [this, key](){
        onClientIncoming(key);
    });

    m_mapClient.insert(key, QPointer(socket));
}

void ClientHandler::onClientIncoming(const QString &key) {
    // qDebug() << "Client" << key << "have something to share";
    QPointer<QTcpSocket> client = m_mapClient[key];

    // qDebug() << (QThread::currentThread() != this->thread() ? "readyRead slot called on another thread" : "readyRead slot called on main thread");

    if (!client) return;
    // Either read or fail fast
    if (client->bytesAvailable() < 5) return;

    client->startTransaction();

    // Read in main thread because QTcpSocket is not thread-safe
    // If reading from another thread, this slot will return before all data is read from the socket
    // Which causes readyRead signal to be emitted again, and again
    // Which spam the threadpool, and potentially corrupt the data stream
    QByteArray header = client->read(5);
    QDataStream inHeader(header);

    quint8 method;
    quint32 size;
    inHeader >> method;
    inHeader >> size;

    // qDebug() << "Message method" << method;
    // qDebug() << "Message size" << size;

    QByteArray data = client->read(size);
    if (data.size() < size) {
        client->rollbackTransaction();
        return;
    }

    client->commitTransaction();

    ReadHandler *readRunnable = new ReadHandler(std::move(data));
    QThreadPool::globalInstance()->start(readRunnable);
}

void ClientHandler::onClientDisconnected(const QString &key) {
    qDebug() << "Client" << key << "disconnected";
    QPointer<QTcpSocket> client = m_mapClient.take(key);

    if (!client) {
        qDebug() << "Disconnected client somehow does not exist in map";
        return;
    }

    // QTcpSocket is a child of QTcpServer, so it exists as long as socket server exists
    // Delete it explicitly
    client->deleteLater();
}

void ClientHandler::onClientError(const QString &key, QAbstractSocket::SocketError error) {
    qDebug() << error;

    onClientDisconnected(key);
}