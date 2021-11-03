#include "GenerationSettingsWidget.h"

GenerationSettingsWidget::GenerationSettingsWidget(QWidget* parent, SimulationModel::Cells::CellFactory* factory)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFactory(factory);
}

GenerationSettingsWidget::~GenerationSettingsWidget()
{
}

void GenerationSettingsWidget::setFactory(SimulationModel::Cells::CellFactory* factory)
{
	this->factory = factory;
}
