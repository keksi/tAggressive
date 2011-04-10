#pragma once

#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>

class QFileSystemModel;
class QSortFilterProxyModel;

namespace Ui
{
    class Taggressive;
}

class Taggressive : public QMainWindow
{
Q_OBJECT

public:
    explicit                  Taggressive(QWidget* parent = 0);
    virtual                   ~Taggressive();

private slots:
    void                      on_actionClose_triggered();
    void                      on_actionEditTag_triggered();
    void                      on_fileTree_clicked(QModelIndex index);

private:
    Ui::Taggressive           *m_ui;
    QFileSystemModel          *m_fsModel;
    QSortFilterProxyModel     *m_fsProxyModel;

    void                      fillFileTable(const QString &dirpath);
    void                      initializeFileTree();
    void                      initializeFileTable();
};
