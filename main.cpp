#include "panel.h"
#include "matrix.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Panel w;
    w.show();

    Matrix m;
    //m.show();

    return a.exec();
}
