#ifndef BASEDAO_H
#define BASEDAO_H

#include <QSqlDatabase>
#include <QSqlError>

class BaseDAO
{
public:
    BaseDAO(const QString &key = "default");
protected:
    QSqlDatabase m_db;
};

#endif // BASEDAO_H
