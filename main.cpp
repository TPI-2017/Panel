#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Panel");
    QCoreApplication::setOrganizationName("Panel-LED");

    Controller a(argc,argv);
    return a.exec();
}
