#ifndef SHIPRADARINFOLISTMODEL_H
#define SHIPRADARINFOLISTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QAbstractListModel>
#include <QMap>

#include "model/ShipRadarInfoModel.h"

class ShipRadarInfoItemModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    ShipRadarInfoItemModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void update(QList<ShipRadarInfoModel> listShipInfo);
private:
    QList<qint64> m_keyLookup{};
    QMap<qint64, ShipRadarInfoModel> m_shipMap{};

    QList<qint64> m_keyInsertBuffer{};


};

#endif // SHIPRADARINFOLISTMODEL_H
