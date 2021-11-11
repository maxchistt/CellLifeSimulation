#pragma once
#include <QWidget>
#include <QColor>

class SimulationView : public QWidget
{
	Q_OBJECT
public:
	virtual void drawItem(int x, int y, int size, QColor color) = 0;
	virtual void clear() = 0;
	SimulationView(QWidget* parent);
	virtual ~SimulationView() = default;
	virtual int width();
	virtual int height();
	virtual void resize3DScene() {};
	virtual void frameComplete() {};
protected:
	void setCentralWidget(QWidget* viewWidget);
private:
	void setupLayout();
};
