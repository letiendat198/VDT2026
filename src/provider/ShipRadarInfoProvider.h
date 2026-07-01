#ifndef SHIPRADARINFOPROVIDER_H
#define SHIPRADARINFOPROVIDER_H

#include <QObject>
#include <QQmlEngine>
#include <QList>
#include <QMutex>
#include <QtConcurrent>

#include <model/ShipRadarInfoModel.h>
#include <dao/ShipRadarInfoDAO.h>

class ShipRadarInfoProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
protected:
    ShipRadarInfoProvider(QObject *parent = nullptr);

    static ShipRadarInfoProvider *m_instance;

public:
    /**
     * Singletons should not be cloneable.
     */
    ShipRadarInfoProvider(ShipRadarInfoProvider &other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const ShipRadarInfoProvider &) = delete;

    static ShipRadarInfoProvider* getInstance() {
        if (!m_instance) m_instance = new ShipRadarInfoProvider();

        return m_instance;
    }

    // Need this so that QML engine can create this class
    static ShipRadarInfoProvider *create(QQmlEngine *qmlEngine, QJSEngine *)
    {
        return getInstance();
    }

    Q_INVOKABLE void requestAllLatest();

    void update(QList<ShipRadarInfoModel> data);

signals:
    void dataReady(QList<ShipRadarInfoModel>);

private:
    bool writeBackToDb(QList<ShipRadarInfoModel> data);
    void populateIntrudeDataFromDb();

    QMutex m_lock{};
    QMap<qint64, ShipRadarInfoModel> m_shipMap{};
    QFuture<void> m_populateFromDbTask;
};

#endif // SHIPRADARINFOPROVIDER_H
