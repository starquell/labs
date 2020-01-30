#ifndef UIUTILS_H
#define UIUTILS_H

#include <QTableView>
#include <QHeaderView>

namespace UIUtils {

    void viewSetup (QTableView* view) {


        view->setSortingEnabled(true);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->hideColumn(0);
        view->setColumnWidth(1, 210);
        view->hideColumn(2);
        view->hideColumn(3);
        view->verticalHeader()->setVisible(false);
        view->show();
    }
}
#endif // UIUTILS_H
