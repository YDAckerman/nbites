#include <QtGui/QApplication>
#include "simulatorwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulatorWindow w;
    w.show();

    return a.exec();
}
