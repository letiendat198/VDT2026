#include "ShipModel.h"

#include <QDataStream>
#include <QIODevice>
#include <QDebug>

ShipModel::ShipModel() {}

ShipModel::ShipModel(const QString &id, const QString &name) : m_id(id),
    m_name(name)
{}

QString ShipModel::id() const
{
    return m_id;
}

void ShipModel::setId(const QString &newId)
{
    m_id = newId;
}

QString ShipModel::name() const
{
    return m_name;
}

void ShipModel::setName(const QString &newName)
{
    m_name = newName;
}

QList<ShipRadarInfoModel> ShipModel::radarInfo() const
{
    return m_radarInfo;
}

void ShipModel::setRadarInfo(const QList<ShipRadarInfoModel> &newRadarInfo)
{
    m_radarInfo = newRadarInfo;
}




