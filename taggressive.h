#pragma once

#include <QMainWindow>

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

private:
    Ui::Taggressive           *m_ui;
};
