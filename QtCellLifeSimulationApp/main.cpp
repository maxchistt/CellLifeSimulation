#include "MainWindowCLS.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>

int main(int argc, char* argv[])
{
	QCoreApplication::setApplicationName(QStringLiteral("C3DShellCodingTutorial"));
	QCoreApplication::setOrganizationName(QStringLiteral("Maxim Chistyakov"));
	QCoreApplication::setOrganizationDomain(QStringLiteral("https://github.com/maxchistt/CellLifeSimulation"));
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	QApplication a(argc, argv);
	MainWindowCLS w;
	w.show();
	return a.exec();
}
