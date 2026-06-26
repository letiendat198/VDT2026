#ifndef READHANDLER_H
#define READHANDLER_H

#include <QRunnable>
#include <QTcpSocket>
#include <QPointer>


class ReadHandler : public QRunnable
{
public:
    ReadHandler(QPointer<QTcpSocket> socket);
private:
    void run() override;

    QPointer<QTcpSocket> m_socket{};
};

#endif // READHANDLER_H
