#ifndef DBQUERING_H
#define DBQUERING_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace DBConfig {

    const inline QString DBType = "QSQLITE";
    const inline QString DBPath = "db.sqlite";

    const inline QString CommonStorage = "notes";
    const inline QString NameField = "name";
    const inline QString ContentField = "content";
    const inline QString IDField = "id";
    const inline QString IsArchivedField = "isArchived";

    enum Storage {Common, Archive};
    enum Fields {ID, Name, Content, isArchived};
}

class DB {
private:
    explicit DB ()
        : m_db (QSqlDatabase::addDatabase(DBConfig::DBType))
    {
        m_db.setDatabaseName(DBConfig::DBPath);

        if (!m_db.open())
            throw std::runtime_error(m_db.lastError().text().toStdString());

        QSqlQuery query (m_db);
        query.prepare(QString("CREATE TABLE IF NOT EXISTS %1"
                      "(%2 INTEGER PRIMARY KEY AUTOINCREMENT,"
                      " %3 TEXT,"
                      " %4 TEXT,"
                      " %5 INTEGER DEFAULT 0)")
                      .arg(DBConfig::CommonStorage)
                      .arg(DBConfig::IDField)
                      .arg(DBConfig::NameField)
                      .arg(DBConfig::ContentField)
                      .arg(DBConfig::IsArchivedField));

        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }

public:
    static auto& get() {
        static DB instance;
        return instance.m_db;
    }

private:
    QSqlDatabase m_db;
};

#endif // DBQUERING_H
