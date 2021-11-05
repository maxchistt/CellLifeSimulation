#include "MainWindowCLS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowCLS w;
    w.show();
    return a.exec();
}
