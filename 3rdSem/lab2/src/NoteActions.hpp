#ifndef NOTESAVER_H
#define NOTESAVER_H

#include "DB.hpp"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

#include <fstream>

namespace NoteActions {

    void exportNotes (const QString& fileName, const QSqlTableModel& model) {

        std::ofstream ofs(fileName.toStdString());

        for (int i = 0; i < model.rowCount(); ++i) {
            auto record = model.record(i);
            ofs << "\n*********************"
                   + record.value(DBConfig::Fields::Name).toString().toStdString()
                   + "*************************\n";
            ofs << record.value(DBConfig::Fields::Content).toString().toStdString();
            ofs << std::endl;
        }
    }
}

#endif // NOTESAVER_H
