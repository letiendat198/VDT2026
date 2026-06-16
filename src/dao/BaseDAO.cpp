#include "BaseDAO.h"

BaseDAO::BaseDAO(const QString &key) {
    // Open a new connection for each key (key should be unique for each thread)
    if (QSqlDatabase::contains(key)) {
        m_db = QSqlDatabase::database(key);
        return;
    }

    m_db = QSqlDatabase::addDatabase("QPSQL", key);

    m_db.setHostName("localhost");
    m_db.setDatabaseName("gisVDT");
    m_db.setUserName("postgres");
    m_db.setPassword("admin");

    bool ok = m_db.open();
    if (!ok) {
        qDebug() << m_db.lastError();
    }
}
