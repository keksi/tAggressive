// Qt/
#include <QDebug>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
// taggressive/
#include "taggressive.h"
#include "ui_taggressive.h"

Taggressive::Taggressive(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::Taggressive)
    , m_fsModel(0)
    , m_fsProxyModel(0)
{
    m_ui->setupUi(this);

    // initialize
    initializeFileTree();
}

Taggressive::~Taggressive()
{
    delete m_ui;
    m_ui = 0;
}

void Taggressive::on_actionClose_triggered()
{
    exit(0);
}

void Taggressive::on_actionEditTag_triggered()
{
    // edit tag
    exit(0);
}

void Taggressive::initializeFileTree()
{
    m_fsModel = new QFileSystemModel(this);
    m_fsModel->setRootPath(QDir::currentPath());
    m_fsModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives);

    m_fsProxyModel = new QSortFilterProxyModel(this);
    m_fsProxyModel->setSourceModel(m_fsModel);
    m_fsProxyModel->setDynamicSortFilter(true);
    m_fsProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);

    m_ui->fileTree->setModel(m_fsProxyModel);
    m_ui->fileTree->setAnimated(true);
    m_ui->fileTree->setAlternatingRowColors(true);
    m_ui->fileTree->sortByColumn(0, Qt::AscendingOrder);
    m_ui->fileTree->setSortingEnabled(true);
    m_ui->fileTree->header()->setResizeMode(QHeaderView::ResizeToContents);
    m_ui->fileTree->header()->hideSection(1);
    m_ui->fileTree->header()->hideSection(2);
    m_ui->fileTree->header()->hideSection(3);
    m_ui->fileTree->setHeaderHidden(true);
}

void Taggressive::on_fileTree_clicked(QModelIndex index)
{
    qDebug("Taggressive::on_fileTree_clicked() : selected '%s'",
        qPrintable(index.data().toString()));
}
