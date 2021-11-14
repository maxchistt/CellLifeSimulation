#include "MainWindowCLS.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include "C3D_USAGE.h"
#ifdef C3D_USAGE
#include <qt_openglwidget.h>
#include <qlogging.h>
#include <last.h>
VSN_USE_NAMESPACE
#endif

int main(int argc, char* argv[])
{
#	if defined(WIN32) && defined(C3D_USAGE)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#	endif
	QCoreApplication::setApplicationName(QStringLiteral("CellLifeSimulation"));
	QCoreApplication::setOrganizationName(QStringLiteral("Maxim Chistyakov"));
	QCoreApplication::setOrganizationDomain(QStringLiteral("https://github.com/maxchistt/CellLifeSimulation"));
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	QApplication a(argc, argv);
#	ifdef C3D_USAGE
	Application vapp;
#	endif
	MainWindowCLS w;
	w.show();
	return a.exec();
}
