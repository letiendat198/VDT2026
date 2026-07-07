#ifndef DIALOGPROVIDER_H
#define DIALOGPROVIDER_H

#include <QObject>
#include <QQmlEngine>

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

    enum Level {
        Notice = 0,
        Warning = 1,
        Error = 2,
        Fatal = 3
    };
signals:
    void dialogRequested(int level, const QString &body);
};

#endif // DIALOGPROVIDER_H
