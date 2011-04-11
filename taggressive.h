#pragma once

// Qt/
#include <QtCore/QMap>
#include <QtCore/QModelIndex>
#include <QtGui/QMainWindow>
// taglib/
#include "taglib.h"
#include "fileref.h"

//--[ forward declarations ]---------------------------------------------------
class QFileSystemModel;
class QSortFilterProxyModel;

//--[ namespaces and typedefs ]------------------------------------------------
typedef QMap<QString, TagLib::FileRef> DirMap;

namespace Ui
{
    class Taggressive;
}

//-----------------------------------------------------------------------------
class Taggressive : public QMainWindow
{
Q_OBJECT

public:
    explicit                  Taggressive(QWidget* parent = 0);
    virtual                   ~Taggressive();

private:
    Ui::Taggressive           *m_ui;
    QFileSystemModel          *m_fsModel;
    QSortFilterProxyModel     *m_fsProxyModel;
    DirMap                    m_selectedDirMap;

    void                      fillFileTable(const QString &dirpath);
    void                      initializeFileTree();
    void                      initializeFileTable();

private slots:
    void                      on_actionClose_triggered();
    void                      on_actionEditTag_triggered();
    void                      on_fileTree_clicked(QModelIndex index);
};
