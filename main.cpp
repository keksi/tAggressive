#include <QtGui/QApplication>
#include "taggressive.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Taggressive w;
    w.show();

    return a.exec();
}
