#include "QtCellLifeSimulationApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCellLifeSimulationApp w;
    w.show();
    return a.exec();
}
