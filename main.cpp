#include "panel.h"
#include "translation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Panel w;
    Translation::translate();
    w.show();
    return a.exec();
}
