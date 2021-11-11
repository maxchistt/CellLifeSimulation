#pragma once
#include "C3D_USAGE.h"

#ifdef C3D_USAGE

#include "SimulationView.h"

#include <qt_openglwidget.h>
#include <vsn_geomsamples.h>
#include <mesh_triangle.h>
#include <mesh.h>
#include <vsn_labelgeometry.h>
#include <qlogging.h>
#include <last.h>

VSN_USE_NAMESPACE

class SimulationViewC3D : public SimulationView
{
	Q_OBJECT
public:
	SimulationViewC3D(QWidget* parent);
	~SimulationViewC3D();
	void drawItem(int x, int y, int size, QColor color) override;
	void clear() override;
private:
	QtVision::QtOpenGLSceneWidget* glWidget;
	void testScene();
	void checkLicense();
};

#endif