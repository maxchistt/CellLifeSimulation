#include "SimulationView.h"
#include <QGraphicsLineItem>
#include <QResizeEvent>

SimulationView::SimulationView(QWidget* parent)
	: QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);
	setStyleSheet("background-image:url(\":/backgrounds/resources/bg.png\");background-position: center;");
	setFrameShape(QFrame::Shape::NoFrame);
	resize(parent->size());
}

void SimulationView::setParent(QWidget* parent)
{
	resize(parent->size());
	QGraphicsView::setParent(parent);
}

void SimulationView::drawItem(int x, int y, int size, QColor color)
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
