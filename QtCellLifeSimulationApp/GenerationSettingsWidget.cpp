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
	prepareColorSelections();

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

void GenerationSettingsWidget::prepareColorSelections()
{
	int index = 0;
	for (auto cellColor : SimulationModel::Cells::ALL_CELL_COLORS) {
		QColor color = ColorConverter::convertColor(cellColor);
		QString colorstr = ColorConverter::convertColorToString(cellColor);
		QString checkBoxStyle = "background-color: " + color.name() + ";" + "border: 3px solid " + color.name() + ";";

		QCheckBox* checkbox_beware = new QCheckBox(this);
		checkbox_beware->setObjectName("colorsBewareCheckbox" + colorstr);
		checkbox_beware->setStyleSheet(checkBoxStyle);
		colorsBeware_checkboxes.push_back(checkbox_beware);
		ui.colorsBewareLayout->addWidget(checkbox_beware);

		QCheckBox* checkbox_hunt = new QCheckBox(this);
		checkbox_hunt->setObjectName("colorsHuntCheckbox" + colorstr);
		checkbox_hunt->setStyleSheet(checkBoxStyle);
		colorsHunt_checkboxes.push_back(checkbox_hunt);
		ui.colorsHuntLayout->addWidget(checkbox_hunt);

		ui.colorComboBox->addItem(colorstr);
		ui.colorComboBox->setItemData(index, color, Qt::BackgroundRole);

		index++;
	}
}

void GenerationSettingsWidget::setEditorDNAParams(SimulationModel::Cells::CellDNA dna_options)
{
	ui.feedDamageDoubleSpinBox->setValue(dna_options.feed_damage);
	ui.maxFoodDoubleSpinBox->setValue(dna_options.max_food);
	ui.maxSpeedDoubleSpinBox->setValue(dna_options.max_speed);
	ui.detectRadiusDoubleSpinBox->setValue(dna_options.detect_radius);
	ui.foodsToDuplicateDoubleSpinBox->setValue(dna_options.foods_to_duplicate);
	ui.stopingFactorDoubleSpinBox->setValue(dna_options.stoping_factor);
	ui.duplChancePercentSpinBox->setValue(dna_options.dupl_chanse_percent);
	ui.duplNearcellsLimitSpinBox->setValue(dna_options.dupl_nearsamecells_limit);
	ui.foodgenNearcellsFactorDoubleSpinBox->setValue(dna_options.foodgen_nearcells_factor);
	ui.neardistanceCalcfactorDoubleSpinBox->setValue(dna_options.neardistance_calcfactor);
	ui.sizeSpinBox->setValue(dna_options.size);
	ui.foodGenerationDoubleSpinBox->setValue(dna_options.food_generation);

	ui.colorComboBox->setCurrentIndex(dna_options.color);

	int index = 0;
	for (auto cellColor : SimulationModel::Cells::ALL_CELL_COLORS) {
		colorsBeware_checkboxes[index]->setChecked(false);
		for (auto color : dna_options.colors_beware) {
			if (color == index) {
				colorsBeware_checkboxes[index]->setChecked(true);
			}
		};

		colorsHunt_checkboxes[index]->setChecked(false);
		for (auto color : dna_options.colors_hunt) {
			if (color == index) {
				colorsHunt_checkboxes[index]->setChecked(true);
			}
		};

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
