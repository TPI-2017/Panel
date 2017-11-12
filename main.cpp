#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Controller a(argc,argv);
    return a.exec();
}
