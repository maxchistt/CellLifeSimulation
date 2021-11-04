#include "GenerationSettingsWidget.h"
#include "ColorConverter.h"
#include <QListWidgetItem>

GenerationSettingsWidget::GenerationSettingsWidget(QWidget* parent, SimulationModel::Cells::CellFactory* factory)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFactory(factory);
	updateTable();
	ui.tabWidget->setCurrentIndex(0);

	connect(ui.button_clear, &QPushButton::clicked, this, &GenerationSettingsWidget::clearAllOptions);
	connect(ui.button_delete, &QPushButton::clicked, this, &GenerationSettingsWidget::deleteSelectedOption);
	connect(ui.button_edit, &QPushButton::clicked, this, &GenerationSettingsWidget::editSelectedOption);
	connect(ui.button_new, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_new);
	connect(ui.button_save, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_save);
	connect(ui.button_reset, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_reset);
}

GenerationSettingsWidget::~GenerationSettingsWidget()
{
}

void GenerationSettingsWidget::setFactory(SimulationModel::Cells::CellFactory* factory)
{
	this->factory = factory;
}

void GenerationSettingsWidget::updateTable()
{
	int index = 0;
	ui.listWidgetOptions->clear();
	for (auto option : factory->getOptions()) {
		auto color = ColorConverter::convertColor(option.dna_options.color);
		QListWidgetItem* item = new QListWidgetItem();
		item->setBackgroundColor(color);
		item->setTextColor(Qt::white);
		item->setText(" " + QString::number(index) + " TypeID: " + QString::number(option.typeID));
		ui.listWidgetOptions->addItem(item);

		index++;
	}
}

void GenerationSettingsWidget::clearAllOptions()
{
	factory->clearOptions();
	updateTable();
}

void GenerationSettingsWidget::deleteSelectedOption()
{
	factory->deleteOption(ui.listWidgetOptions->row(ui.listWidgetOptions->currentItem()));
	updateTable();
}

void GenerationSettingsWidget::editSelectedOption()
{
	ui.tabWidget->setCurrentIndex(1);
}

void GenerationSettingsWidget::editor_new()
{
}

void GenerationSettingsWidget::editor_reset()
{
}

void GenerationSettingsWidget::editor_save()
{
}
