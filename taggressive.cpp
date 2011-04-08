#include "taggressive.h"
#include "ui_taggressive.h"

Taggressive::Taggressive(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::Taggressive)
{
    m_ui->setupUi(this);
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
