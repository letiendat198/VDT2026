#include "model/ShipRadarInfoItemModel.h"

#include <QtConcurrent>
#include <QSet>

ShipRadarInfoItemModel::ShipRadarInfoItemModel(QObject *parent) : QAbstractListModel(parent), m_watcher(this) {
    m_insertCount = 0;
    m_removeCount = 0;
    connect(&m_watcher, &QFutureWatcher<void>::finished, this, [this](){
        if (m_insertCount) {
            this->insertRows(0, m_insertCount, QModelIndex());
        }
        if (m_removeCount) {
            this->removeRows(0, m_removeCount, QModelIndex());
        }
    });
}

int ShipRadarInfoItemModel::rowCount(const QModelIndex &parent) const
{
    return m_shipList.size();
}

QVariant ShipRadarInfoItemModel::data(const QModelIndex &index, int role) const
{
    return QVariant::fromValue(m_shipList[index.row()]);
}

// Unused. I'd rather swap underlining list
bool ShipRadarInfoItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    m_shipList[index.row()] = value.value<ShipRadarInfoModel>();

    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags ShipRadarInfoItemModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable;
}

bool ShipRadarInfoItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    // Every time we need to insert, just have to insert in the beginning with the correct count
    // No need to be exact with row number because it doesn't matter on a map
    beginInsertRows(QModelIndex(), 0, count - 1);
    endInsertRows();

    return true;
}

bool ShipRadarInfoItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), 0, count - 1);
    endRemoveRows();

    return true;
}

QHash<int, QByteArray> ShipRadarInfoItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "shipData";
    return roles;
}

void ShipRadarInfoItemModel::update(QList<ShipRadarInfoModel> listShipInfo)
{
    QFuture<void> future = QtConcurrent::run([this, listShipInfo](){
        this->parseData(listShipInfo);
    });

    m_watcher.setFuture(future);
    // qDebug() << m_keyLookup;
}

void ShipRadarInfoItemModel::parseData(QList<ShipRadarInfoModel> listShipInfo)
{
    // We only care about the total number of rows increase or decrease
    if (listShipInfo.size() > m_shipList.size()) {
        m_insertCount = listShipInfo.size() - m_shipList.size();
        m_removeCount = 0;
    }
    else {
        m_removeCount = m_shipList.size() - listShipInfo.size();
        m_insertCount = 0;
    }

    m_shipList.swap(listShipInfo);

    for (int i=0;i<m_shipList.size();i++) {
        QModelIndex index = createIndex(i, 0);
        emit dataChanged(index, index);
    }
}

