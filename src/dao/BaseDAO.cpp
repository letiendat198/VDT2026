#include "BaseDAO.h"

#include <QSettings>
#include <provider/DialogProvider.h>

// Open a new DB connection for each key (key should be unique for each thread)
BaseDAO::BaseDAO(const QString &key) {
    if (QSqlDatabase::contains(key)) {
        // qDebug() << "Using existed database for" << key;
        m_db = QSqlDatabase::database(key);
        return;
    }

    qDebug() << "Creating database connection for" << key;

    QSettings settings;
    QString dbHost = settings.value("dbHost", "").toString();
    int dbPort = settings.value("dbPort", 0).toInt();
    QString dbName = settings.value("dbName", "").toString();
    QString dbUsername = settings.value("dbUsername", "").toString();
    QString dbPassword = settings.value("dbPassword", "").toString();
    // qDebug() <<dbHost;

    m_db = QSqlDatabase::addDatabase("QPSQL", key);

    m_db.setHostName(dbHost);
    m_db.setPort(dbPort);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(dbUsername);
    m_db.setPassword(dbPassword);

    bool ok = m_db.open();
    if (!ok) {
        qDebug() << m_db.lastError();
        DialogProvider::getInstance()->requestDialog(DialogProvider::Level::Fatal, m_db.lastError().text());
    }
}
