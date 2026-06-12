#ifndef SHIPMODEL_H
#define SHIPMODEL_H

#include <QString>
#include <QList>

#include "model/ShipRadarInfoModel.h"

class ShipModel
{
public:
    ShipModel();
    ShipModel(const QString &id, const QString &name);

    QString id() const;
    void setId(const QString &newId);
    QString name() const;
    void setName(const QString &newName);
    QList<ShipRadarInfoModel> radarInfo() const;
    void setRadarInfo(const QList<ShipRadarInfoModel> &newRadarInfo);

private:
    QString m_id{};
    QString m_name{};
    QList<ShipRadarInfoModel> m_radarInfo{};
};

#endif // SHIPMODEL_H
