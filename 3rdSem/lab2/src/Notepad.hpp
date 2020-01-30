#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "DB.hpp"

#include <QMainWindow>
#include <QSqlTableModel>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:

    void changeStorage();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionDelete_triggered();

    void on_actionName_triggered();

    void on_actionDate_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionExport_triggered();

    void on_actionThrowToOtherStorage_triggered();

    void on_actionSwitchStorage_triggered();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QSqlTableModel> model;
    DBConfig::Storage m_storage = DBConfig::Storage::Common;
};
#endif // MAINWINDOW_HPP
