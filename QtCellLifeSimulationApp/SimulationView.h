#pragma once
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "SimulationModel.h"

using namespace SimulationModel;

class SimulationView : public QGraphicsView
{
	Q_OBJECT
public:
	SimulationView(QGraphicsView* parent = 0);
	~SimulationView() {};
	void drawCircle(int x, int y, int size, QColor color);
	void clear();
signals:

public slots:

private:
	QGraphicsView* view;
	QGraphicsScene* scene;
protected:
	void resizeEvent(QResizeEvent* event);
};
