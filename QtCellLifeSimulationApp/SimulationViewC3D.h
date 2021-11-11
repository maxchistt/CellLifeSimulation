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
	void addDrawItem(int x, int y, int size, QColor color) override;
	void clear() override;
	void resize3DScene() override;
	void frameComplete() override;
private:
	struct DrawItem {
		int x;
		int y;
		float size;
		Color color;
	};
	int process = 0;
	bool processStartCheck();
	void processEndCheck();
	std::vector<DrawItem> frame;
	QtVision::QtOpenGLSceneWidget* glWidget;
	void prepareScene();
	void checkLicense();
};

#endif