#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QMap>
#include <QTcpSocket>

class ClientHandler : public QObject
{
    Q_OBJECT
protected:
    ClientHandler();

    static ClientHandler *m_instance;

public:
    /**
     * Singletons should not be cloneable.
     */
    ClientHandler(ClientHandler &other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const ClientHandler &) = delete;

    static ClientHandler* getInstance() {
        if (!m_instance) m_instance = new ClientHandler();

        return m_instance;
    }

    void addClient(QTcpSocket*);
private slots:
    void onClientDisconnected(int key);
    void onClientError(int key, QAbstractSocket::SocketError error);
    // TODO: Handle clear all clients when socket server closes

private:
    // Identify by server socket port, maybe bad :D
    QMap<int, QTcpSocket*> m_mapClient{};
};

#endif // CLIENTHANDLER_H
