#include "SimulationView.h"
#include <QGraphicsLineItem>
#include <QResizeEvent>

SimulationView::SimulationView(QGraphicsView* parent)
	: QGraphicsView(parent)
{
	view = new QGraphicsView();
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, view->width(), view->height());
	setScene(scene);
}

void SimulationView::drawCircle(int x, int y, int size, QColor color)
{
	scene->addEllipse(x, y, size, size, Qt::NoPen, color);
}

void SimulationView::clear()
{
	scene->clear();
}

void SimulationView::resizeEvent(QResizeEvent* event)
{
	scene->setSceneRect(0, 0, event->size().width(), event->size().height());
	QGraphicsView::resizeEvent(event);
}