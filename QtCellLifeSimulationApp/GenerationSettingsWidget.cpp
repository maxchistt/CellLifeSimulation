#include "GenerationSettingsWidget.h"

GenerationSettingsWidget::GenerationSettingsWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GenerationSettingsWidget::~GenerationSettingsWidget()
{
}

void GenerationSettingsWidget::setFactory(SimulationModel::Cells::CellFactory* factory)
{
	this->factory = factory;
}
