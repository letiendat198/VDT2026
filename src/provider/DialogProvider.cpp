#include "DialogProvider.h"

DialogProvider* DialogProvider::m_instance = nullptr;

DialogProvider::DialogProvider(QObject *parent) : QObject(parent), m_messageQueue(), m_displayComponentAvailable(false) {}

void DialogProvider::requestDialog(int level, const QString &body)
{
    // Queue a message
    // If queue is free and QML dialog component is available, notify it
    m_messageQueue.enqueue(DialogMessage{level, body});

    qDebug() << "Queuing dialog at position" << m_messageQueue.size();

    if (m_displayComponentAvailable && m_messageQueue.size() == 1) {
        notifyDialogQueueHead();
    }
}

void DialogProvider::setDisplayComponentAvailable(bool available)
{
    m_displayComponentAvailable = available;

    if (available) notifyDialogQueueHead();
}

// When dialog QML component done displaying the dialog, it will pop the queue itself
void DialogProvider::popDialogQueue()
{
    if (m_messageQueue.isEmpty()) return;

    qDebug() << "Popping queue";

    m_messageQueue.dequeue();
    notifyDialogQueueHead();
}

void DialogProvider::notifyDialogQueueHead()
{
    if (m_messageQueue.isEmpty()) return;

    qDebug() << "Notify QML";

    DialogMessage message = m_messageQueue.head();
    emit dialogRequested(message.level, message.message);
}
