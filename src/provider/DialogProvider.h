#ifndef DIALOGPROVIDER_H
#define DIALOGPROVIDER_H

#include <QObject>
#include <QQmlEngine>
#include <QQueue>

struct DialogMessage {
    int level;
    QString message;
};

class DialogProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
protected:
    DialogProvider(QObject *parent = nullptr);

    static DialogProvider *m_instance;

public:
    /**
     * Singletons should not be cloneable.
     */
    DialogProvider(DialogProvider &other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const DialogProvider &) = delete;

    static DialogProvider* getInstance() {
        if (!m_instance) m_instance = new DialogProvider();

        return m_instance;
    }

    // Need this so that QML engine can create this class
    static DialogProvider *create(QQmlEngine *qmlEngine, QJSEngine *)
    {
        return getInstance();
    }

    Q_INVOKABLE void requestDialog(int level, const QString &body);
    Q_INVOKABLE void setDisplayComponentAvailable(bool available);
    Q_INVOKABLE void popDialogQueue();

    void notifyDialogQueueHead();

    enum Level {
        Notice = 0,
        Warning = 1,
        Error = 2,
        Fatal = 3
    };
signals:
    void dialogRequested(int level, const QString &body);

private:
    // First item on message queue is the dialog currently displayed
    QQueue<DialogMessage> m_messageQueue{};
    bool m_displayComponentAvailable{};
};

#endif // DIALOGPROVIDER_H
