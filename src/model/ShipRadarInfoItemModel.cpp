#include "model/ShipRadarInfoItemModel.h"


ShipRadarInfoItemModel::ShipRadarInfoItemModel(QObject *parent) : QAbstractListModel(parent){}

int ShipRadarInfoItemModel::rowCount(const QModelIndex &parent) const
{
    return m_shipMap.size();
}

QVariant ShipRadarInfoItemModel::data(const QModelIndex &index, int role) const
{
    qint64 key = m_keyLookup[index.row()];

    return QVariant::fromValue(m_shipMap[key]);
}

bool ShipRadarInfoItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qint64 key = m_keyLookup[index.row()];

    ShipRadarInfoModel model = value.value<ShipRadarInfoModel>();

    m_shipMap[key] = model;

    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags ShipRadarInfoItemModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable;
}

bool ShipRadarInfoItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row+count);
    m_keyLookup.append(m_keyInsertBuffer);
    endInsertRows();

    m_keyInsertBuffer.clear();

    return true;
}

bool ShipRadarInfoItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

QHash<int, QByteArray> ShipRadarInfoItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "shipData";
    return roles;
}

void ShipRadarInfoItemModel::update(QList<ShipRadarInfoModel> listShipInfo)
{
    Q_FOREACH(ShipRadarInfoModel ship, listShipInfo) {
        if (!m_shipMap.contains(ship.shipId())) {
            m_keyInsertBuffer.append(ship.shipId());
            m_shipMap[ship.shipId()] = ship;
        }

        else {
            QModelIndex index = createIndex(m_keyLookup.indexOf(ship.shipId()), 0);
            // qDebug() << "Data already exists at index: "<< index.row();
            setData(index, QVariant::fromValue(ship), 0);
        }
    }


    if (!m_keyInsertBuffer.empty()) {
        insertRows(m_keyLookup.size(), m_keyInsertBuffer.size(), QModelIndex());
    }

    // qDebug() << m_keyLookup;
}

