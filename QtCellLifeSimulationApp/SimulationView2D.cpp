#include "SimulationView2D.h"

SimulationView2D::SimulationView2D(QWidget* parent)
	: SimulationView(parent)
{
	view = new AdaptiveQGraphicsView(this);
	view->setStyleSheet("background-image:url(\":/backgrounds/resources/bg.png\");background-position: center;");
	view->setFrameShape(QFrame::Shape::NoFrame);
	setCentralWidget(view);
}

SimulationView2D::~SimulationView2D()
{
	delete view;
}

void SimulationView2D::drawItem(int x, int y, int size, QColor color)
{
	view->scene()->addEllipse(x, y, size, size, Qt::NoPen, color);
}

void SimulationView2D::clear()
{
	view->scene()->clear();
}