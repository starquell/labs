#include "Notepad.hpp"
#include "NoteActions.hpp"
#include "DB.hpp"
#include "UIUtils.hpp"
#include "ui_MainWindow.h"

#include <QInputDialog>
#include <QSqlTableModel>
#include <QAbstractItemModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(std::make_shared<QSqlTableModel>(this, DB::get()))
{
    ui->setupUi(this);

    model->setTable(DBConfig::CommonStorage);
    model->setFilter(QString("%1 = '%2'")
                     .arg(DBConfig::IsArchivedField)
                     .arg(0));
    model->select();

    ui->tableView->setModel(model.get());
    UIUtils::viewSetup(ui->tableView);
}


Notepad::~Notepad()
{
    delete ui;
}

void Notepad::changeStorage() {
    m_storage = (m_storage == DBConfig::Storage::Common)
                ? DBConfig::Storage::Archive
                : DBConfig::Storage::Common;
    ui->actionSwitchStorage->setText(m_storage == DBConfig::Storage::Common
                                          ? "Switch to archive"
                                          : "Switch to common storage");
    ui->actionThrowToOtherStorage->setText(m_storage == DBConfig::Storage::Common
                                            ? "Throw to archive"
                                            : "Move to common storage");

}

void Notepad::on_actionNew_triggered()
{
    if (m_storage == DBConfig::Storage::Archive) {
        QMessageBox::information(this, "Info", "You can't create notes at archive.");
        return;
    }
    QString newFileName = QInputDialog::getText(this, QString ("New Note"),
                                                      QString ("Enter name for new file wisely"));
    ui->textEdit->setText(QString());
    model->insertRow(model->rowCount());

    model->setData(model->index(model->rowCount() - 1, 1), newFileName);
    if (!model->submitAll())
        QMessageBox::information(this, "Error", model->lastError().text());
}

void Notepad::on_actionSave_triggered()
{
    auto selected = ui->tableView->selectionModel()->selectedIndexes();
    if (selected.size() == 0) {
       QMessageBox::warning(this, "Info", "No data.");
       return;
    }

    model->setData(selected.at(0).siblingAtColumn(2), ui->textEdit->toPlainText());
    QMessageBox::information(this, "Info", "Note saved.");
    if (!model->submitAll())
        QMessageBox::information(this, "Error", model->lastError().text());

}

void Notepad::on_tableView_doubleClicked(const QModelIndex &index)
{
    ui->textEdit->setText(index.siblingAtColumn(2).data().toString());
}

void Notepad::on_actionDelete_triggered()
{
    model->removeRow(ui->tableView->selectionModel()->selectedIndexes().at(0).row());
    if (!model->submitAll())
        QMessageBox::information(this, "Error", model->lastError().text());
    model->select();
}

void Notepad::on_actionName_triggered()
{
    model->setSort(1, Qt::SortOrder::AscendingOrder);
    model->select();
}

void Notepad::on_actionDate_triggered()
{
    model->setSort(0, Qt::SortOrder::AscendingOrder);
    model->select();
}

void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}

void Notepad::on_actionExport_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                     tr("Choose directory for export file"),
                                                     "/home");
    try {
        NoteActions::exportNotes(path + "/exportedNotes.txt", *model);
    } catch (...) {
        QMessageBox::warning(this, "Error",
                             QString("Unable to export notes to '%1'.").arg(path + "/exportedNotes.txt"));
    }

}


void Notepad::on_actionThrowToOtherStorage_triggered()
{
    if (ui->tableView->selectionModel()->selectedIndexes().size() == 0)
        return;
    auto selected = ui->tableView->selectionModel()->selectedIndexes().at(0);
    model->setData(selected.siblingAtColumn(DBConfig::Fields::isArchived),
                   m_storage == DBConfig::Storage::Common ? 1 : 0);
    if (!model->submitAll())
        QMessageBox::information(this, "Error", model->lastError().text());
    model->select();
}

void Notepad::on_actionSwitchStorage_triggered()
{
    model->setFilter(QString("%1 = '%2'")
                     .arg(DBConfig::IsArchivedField)
                     .arg(m_storage == DBConfig::Storage::Common ? 1 : 0));
    model->select();
    ui->textEdit->setText("");
    changeStorage();
}
