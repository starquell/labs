#ifndef SQLMODELCONFIGURATOR_HPP
#define SQLMODELCONFIGURATOR_HPP

#include <memory>

#include <QSqlTableModel>

#include "DB.hpp"

class SqlNoteModel : public QSqlTableModel {

public:

    explicit SqlNoteModel(QObject* parent);

    void setTable (const QString& tableName);

private:
    void setView ();


private:
    QString m_table = DBConfig::CommonStorage;
};

#endif // SQLMODELCONFIGURATOR_HPP
