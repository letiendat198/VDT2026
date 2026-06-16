#ifndef READHANDLER_H
#define READHANDLER_H

#include <QRunnable>
#include <QTcpSocket>
#include <QPointer>


class ReadHandler : public QRunnable
{
public:
    // Key is used to choose a database connection
    ReadHandler(QPointer<QTcpSocket> socket, int key);
private:
    void run() override;

    QPointer<QTcpSocket> m_socket{};
    int m_key{};
};

#endif // READHANDLER_H
