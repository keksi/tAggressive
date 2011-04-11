// Qt/
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtGui/QTableWidget>
#include <QtGui/QFileSystemModel>
#include <QtGui/QSortFilterProxyModel>
// taggressive/
#include "taggressive.h"
#include "ui_taggressive.h"
// taglib/
#include "tag.h"

//--[ defines ]----------------------------------------------------------------
#define START_DIRECTORY "/home/tomjoad/Musik/Alben/"

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
Taggressive::~Taggressive()
{
    delete m_ui;
    m_ui = 0;
}

//-----------------------------------------------------------------------------
void Taggressive::fillFileTable(const QString &dirpath)
{
    m_selectedDirMap.clear();
    QDir albumDir(dirpath);
    QFileInfoList tracklist = albumDir.entryInfoList(QStringList() << "*.mp3");
    m_ui->fileTable->setRowCount(tracklist.size());

    for (int i=0; i < tracklist.size(); ++i)
    {
        QFileInfo fileInfo = tracklist.at(i);
        TagLib::FileRef fileRef(qPrintable(fileInfo.filePath()));
        m_selectedDirMap.insert(fileInfo.fileName(), fileRef);

        m_ui->fileTable->setItem(
            i, 0, new QTableWidgetItem(fileInfo.fileName()));
        m_ui->fileTable->setItem(
            i, 1, new QTableWidgetItem(fileRef.tag()->artist().toCString()));
        m_ui->fileTable->setItem(
            i, 2, new QTableWidgetItem(fileRef.tag()->album().toCString()));
        m_ui->fileTable->setItem(
            i, 3, new QTableWidgetItem(fileRef.tag()->title().toCString()));
        m_ui->fileTable->setItem(
            i, 4, new QTableWidgetItem(QString::number(fileRef.tag()->year())));
        m_ui->fileTable->setItem(
            i, 5, new QTableWidgetItem(fileRef.tag()->genre().toCString()));
        m_ui->fileTable->setItem(
            i, 6, new QTableWidgetItem(QString::number(fileRef.tag()->track())));
        m_ui->fileTable->setItem(
            i, 7, new QTableWidgetItem(QString::number(fileRef.audioProperties()->bitrate())));
        m_ui->fileTable->setItem(
            i, 8, new QTableWidgetItem(QString("%1:%2")
                .arg(fileRef.audioProperties()->length()/60)
                .arg(fileRef.audioProperties()->length()%60)));
    }
}

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
void Taggressive::initializeFileTable()
{
    m_ui->fileTable->setAlternatingRowColors(true);
    m_ui->fileTable->sortItems(0);
    m_ui->fileTable->setColumnCount(9);
    m_ui->fileTable->setHorizontalHeaderLabels(
        QStringList() << "File name" << "Artist" << "Album" << "Title" << "Year"
                      << "Genre" << "Track #" << "Bitrate" << "Time");
}

//-----------------------------------------------------------------------------
void Taggressive::on_actionClose_triggered()
{
    exit(0);
}

//-----------------------------------------------------------------------------
void Taggressive::on_actionEditTag_triggered()
{
    // TODO: display edit tags dialog in here
}

//-----------------------------------------------------------------------------
void Taggressive::on_fileTree_clicked(QModelIndex index)
{
    QString path = m_fsModel->filePath(m_fsProxyModel->mapToSource(index));
    fillFileTable(path);
    qDebug("Taggressive::on_fileTree_clicked() : displaying contents of '%s'",
        qPrintable(path));
}
