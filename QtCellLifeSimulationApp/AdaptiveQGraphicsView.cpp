#include "AdaptiveQGraphicsView.h"

AdaptiveQGraphicsView::AdaptiveQGraphicsView(QWidget* parent)
	: QGraphicsView(parent)
{
	setScene(new QGraphicsScene(this));
}

AdaptiveQGraphicsView::~AdaptiveQGraphicsView()
{
	delete scene();
}

void AdaptiveQGraphicsView::resizeEvent(QResizeEvent* event)
{
	QGraphicsView::resizeEvent(event);
	scene()->setSceneRect(0, 0, QGraphicsView::width(), QGraphicsView::height());
}
