#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent, int port);
    ~Server();

public slots:
    void onNewConnection();
    void onPendingConnectionAvailable();

private:
    QTcpServer m_server;

};

#endif // SERVER_H
