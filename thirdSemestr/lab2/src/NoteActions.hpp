#ifndef NOTESAVER_H
#define NOTESAVER_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <fstream>

#include "DB.hpp"

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

  //  void moveToArchive ()
}

#endif // NOTESAVER_H
