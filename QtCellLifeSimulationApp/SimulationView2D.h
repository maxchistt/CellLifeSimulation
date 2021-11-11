#pragma once
#include "SimulationView.h"
#include "AdaptiveQGraphicsView.h"

class SimulationView2D : public SimulationView
{
	Q_OBJECT
public:
	SimulationView2D(QWidget* parent);
	~SimulationView2D();
	void drawItem(int x, int y, int size, QColor color) override;
	void clear() override;
private:
	AdaptiveQGraphicsView* view;
};
