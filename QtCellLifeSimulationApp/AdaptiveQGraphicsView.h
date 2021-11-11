#pragma once
#include <QGraphicsView>

class AdaptiveQGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	AdaptiveQGraphicsView(QWidget* parent);
	~AdaptiveQGraphicsView();
protected:
	void resizeEvent(QResizeEvent* event);
};
