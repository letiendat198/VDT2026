#include "BaseDAO.h"

BaseDAO::BaseDAO() {
    // If contain default database connection then don't add it again
    if (QSqlDatabase::contains()) {
        m_db = QSqlDatabase::database();
        return;
    }

    m_db = QSqlDatabase::addDatabase("QPSQL");

    m_db.setHostName("loclahost");
    m_db.setDatabaseName("gisVDT");
    m_db.setUserName("postgres");
    m_db.setPassword("admin");

    bool ok = m_db.open();
    if (!ok) {
        qDebug() << m_db.lastError();
    }
}
