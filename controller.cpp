#include "controller.h"
#include "panel.h"
#include "translation.h"

Controller::Controller(int &argc, char ** argv):
    QApplication(argc,argv)
{
    Panel *w = new Panel();
    Translation::translate();
    w->show();
}
