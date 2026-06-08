#include "Server.h"
#include "socket/ClientHandler.h"

#include <QDebug>

Server::Server(QObject *parent, int port) : m_server(parent) {
    connect(&m_server, &QTcpServer::newConnection, this, &Server::onNewConnection);
    connect(&m_server, &QTcpServer::pendingConnectionAvailable, this, &Server::onPendingConnectionAvailable);

    m_server.listen(QHostAddress::Any, port);
}

Server::~Server() {
    m_server.close();
}

void Server::onNewConnection() {
    qDebug() << "New connection";
}

void Server::onPendingConnectionAvailable() {
    qDebug() << "Pending connection";

    QTcpSocket *client = m_server.nextPendingConnection();

    if (!client) return;

    ClientHandler *clientHandler = ClientHandler::getInstance();
    clientHandler->addClient(client);
}