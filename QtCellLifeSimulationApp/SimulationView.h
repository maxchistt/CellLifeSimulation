#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include "SimulationModel.h"

using namespace SimulationModel;

class SimulationView : public QGraphicsView
{
	Q_OBJECT

public:
	SimulationView(QWidget* parent = Q_NULLPTR);
	void setParent(QWidget* parent);
	void drawCircle(int x, int y, int size, QColor color);
	void clear();

signals:

public slots:

private:
	QGraphicsScene* scene;
protected:
	void resizeEvent(QResizeEvent* event);
};
