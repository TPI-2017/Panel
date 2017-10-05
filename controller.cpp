#include "controller.h"
#include "login.h"
#include "panel.h"
#include "translation.h"

Controller::Controller(int &argc, char ** argv):
    QApplication(argc,argv)
{
    Login *l = new Login();
    Panel *w = new Panel();

    connect(w, SIGNAL(disconnect()), l, SLOT(showWindow()));
    connect(l, SIGNAL(accessPermited()), w, SLOT(showWindow()));

    Translation::translate();
    l->show();
}
