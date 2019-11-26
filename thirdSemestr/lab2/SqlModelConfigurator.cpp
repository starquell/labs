#include "SqlModelConfigurator.hpp"

#include <QSqlQuery>

SqlNoteModel::SqlNoteModel(QObject* parent)
       : QSqlTableModel(parent, DB::get())
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setView();
}

void SqlNoteModel::setTable (const QString& tableName) {
    m_table = tableName;
}

void SqlNoteModel::setView () {

    setQuery(QSqlQuery(QString("SELECT %1, %2, %3 FROM %4")
                                       .arg(DBConfig::IDField)
                                       .arg(DBConfig::NameField)
                                       .arg(DBConfig::ContentField)
                                       .arg(m_table)));
    setHeaderData(0, Qt::Horizontal, tr("Notes"));
}

