// Qt/
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtGui/QTableWidget>
#include <QtGui/QFileSystemModel>
#include <QtGui/QSortFilterProxyModel>
// taggressive/
#include "taggressive.h"
#include "ui_taggressive.h"
// taglib
#include "taglib.h"
#include "tag.h"
#include "fileref.h"

Taggressive::Taggressive(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::Taggressive)
    , m_fsModel(0)
    , m_fsProxyModel(0)
{
    m_ui->setupUi(this);

    // initialize
    initializeFileTree();
    initializeFileTable();
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
    // TODO: display edit tags dialog in here
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

void Taggressive::initializeFileTable()
{
    m_ui->fileTable->setAlternatingRowColors(true);
    m_ui->fileTable->sortItems(0);
    m_ui->fileTable->setColumnCount(4);
    m_ui->fileTable->setHorizontalHeaderLabels(
        QStringList() << "filename" << "artist" << "tracktitle" << "tracknumber");
}

void Taggressive::fillFileTable(const QString &dirpath)
{
    QDir albumDir(dirpath);
    QFileInfoList tracklist = albumDir.entryInfoList(QStringList() << "*.mp3");
    m_ui->fileTable->setRowCount(tracklist.size());

    for (int i=0; i < tracklist.size(); ++i)
    {
        QFileInfo fileInfo = tracklist.at(i);
        TagLib::FileRef fileRef(qPrintable(fileInfo.filePath()));
        QString artist(fileRef.tag()->artist().toCString());
        QString title(fileRef.tag()->title().toCString());
        uint tracknumber(fileRef.tag()->track());

        QTableWidgetItem *filename = new QTableWidgetItem(fileInfo.fileName());
        m_ui->fileTable->setItem(i, 0, filename);
        m_ui->fileTable->setItem(i, 1, new QTableWidgetItem(artist));
        m_ui->fileTable->setItem(i, 2, new QTableWidgetItem(title));
        m_ui->fileTable->setItem(i, 3, new QTableWidgetItem(QString::number(tracknumber)));
    }
}

void Taggressive::on_fileTree_clicked(QModelIndex index)
{
    QString path = m_fsModel->filePath(m_fsProxyModel->mapToSource(index));
    fillFileTable(path);
    qDebug("Taggressive::on_fileTree_clicked() : displaying contents of '%s'",
        qPrintable(path));
}
