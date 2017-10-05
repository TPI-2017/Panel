#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QApplication>

class Controller : public QApplication
{
public:
    Controller(int &argc, char* argv[]);
};

#endif // CONTROLLER_H
