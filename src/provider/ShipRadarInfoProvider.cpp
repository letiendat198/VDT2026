#include "ShipRadarInfoProvider.h"

#include <QThreadPool>

ShipRadarInfoProvider *ShipRadarInfoProvider::m_instance = nullptr;

ShipRadarInfoProvider::ShipRadarInfoProvider(QObject *parent) : QObject(parent) {}

void ShipRadarInfoProvider::requestAllLatest() {
    // qDebug() << "Lastest radar info requested";
    // TODO: Make this async

    // QThreadPool::globalInstance()->start([this]() {
    //     quintptr threadAddr = reinterpret_cast<quintptr>(QThread::currentThread());
    //     ShipRadarInfoDAO dao = ShipRadarInfoDAO(QString::number(threadAddr));
    //     QList<ShipRadarInfoModel> data = dao.getAllLastest();

    //     emit dataReady(data);
    // });

    // Only call populate again if it's not running. Avoid two populate thread
    // Not that it's gonna bug out, but it would be redundant
    // We already accept that this can delay
    if (!m_populateFromDbTask.isRunning()) {
        m_populateFromDbTask = QtConcurrent::run([this]{
            this->populateIntrudeDataFromDb();
        });
    }

    emit dataReady(m_shipMap.values());
}

// Can be called from another thread
void ShipRadarInfoProvider::update(QList<ShipRadarInfoModel> data)
{
    // QThreadPool::globalInstance()->start([this, data]() {
        m_lock.lock();
        Q_FOREACH(ShipRadarInfoModel ship, data) {
            // If already existed and this data is older than currently, skip
            if (m_shipMap.contains(ship.shipId()) && ship.timestamp() < m_shipMap[ship.shipId()].timestamp()) {
                continue;
            }
            // Potential crash. But QMap should return a default inited instance anyways
            m_shipMap[ship.shipId()].copyExceptCrossedWatchPolygon(ship);
        }

        m_lock.unlock();

        this->writeBackToDb(data);
    // });
}

bool ShipRadarInfoProvider::writeBackToDb(QList<ShipRadarInfoModel> data)
{
    // Since we can't use QThread::currentThreadId() because Qt warned against using it
    // Next best thing is probably thread addr. Hope it doesn't get reallocated...
    // But, if it does, shouldn't it considered a new thread anyways
    quintptr threadAddr = reinterpret_cast<quintptr>(QThread::currentThread());

    ShipRadarInfoDAO shipInfoDAO(QString::number(threadAddr));

    return shipInfoDAO.insertMany(data);
}

void ShipRadarInfoProvider::populateIntrudeDataFromDb()
{
    quintptr threadAddr = reinterpret_cast<quintptr>(QThread::currentThread());
    ShipRadarInfoDAO dao = ShipRadarInfoDAO(QString::number(threadAddr));
    QList<ShipRadarInfoModel> data = dao.getAllLastest();

    Q_FOREACH(ShipRadarInfoModel ship, data) {
        if (!m_shipMap.contains(ship.shipId())) continue;

        m_shipMap[ship.shipId()].setListCrossedWatchPolygonId(ship.listCrossedWatchPolygonId());
    }
}
