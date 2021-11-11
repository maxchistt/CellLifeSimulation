#include "SimulationView.h"
#include <QHBoxLayout>

SimulationView::SimulationView(QWidget* parent)
	: QWidget(parent)
{
	setContentsMargins(0, 0, 0, 0);
	setupLayout();
}

int SimulationView::width()
{
	return this->QWidget::width();
}

int SimulationView::height()
{
	return this->QWidget::height();
}

void SimulationView::setCentralWidget(QWidget* viewWidget)
{
	setupLayout();
	for (auto child : this->QWidget::layout()->findChildren<QWidget*>()) {
		this->QWidget::layout()->removeWidget(child);
	}
	this->QWidget::layout()->addWidget(viewWidget);
}

void SimulationView::setupLayout()
{
	if (this->QWidget::layout() == Q_NULLPTR) this->QWidget::setLayout(new QHBoxLayout(this));
	this->QWidget::layout()->setContentsMargins(0, 0, 0, 0);
	this->QWidget::layout()->setMargin(0);
}
