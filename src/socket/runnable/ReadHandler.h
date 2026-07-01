#ifndef READHANDLER_H
#define READHANDLER_H

#include <QRunnable>
#include <QTcpSocket>
#include <QPointer>


class ReadHandler : public QRunnable
{
public:
    ReadHandler(QByteArray data);
private:
    void run() override;

    QByteArray m_data;
};

#endif // READHANDLER_H
