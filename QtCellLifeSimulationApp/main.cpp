#include "MainWindowCLS.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>

#include <qt_openglwidget.h>
#include <qlogging.h>
#include <last.h>

VSN_USE_NAMESPACE

int main(int argc, char* argv[])
{

	QCoreApplication::setApplicationName(QStringLiteral("C3DShellCodingTutorial"));
	QCoreApplication::setOrganizationName(QStringLiteral("Maxim Chistyakov"));
	QCoreApplication::setOrganizationDomain(QStringLiteral("https://github.com/maxchistt/CellLifeSimulation"));
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	QApplication a(argc, argv);
    Application vapp;
	MainWindowCLS w;
	w.show();
	return a.exec();
}
