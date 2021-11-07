#include "GenerationSettingsWidget.h"
#include "ColorConverter.h"
#include <QListWidgetItem>
#define ANY_STR "Any"

using namespace SimulationModel;
using namespace Cells;

GenerationSettingsWidget::GenerationSettingsWidget(QWidget* parent, SimulationModel::Cells::CellFactory* factory)
	: QWidget(parent)
{
	ui.setupUi(this);
	generateColorSelectionEditorControls();
	setCellFactory(factory);
	ui.tabWidget->setCurrentIndex(0);

	connect(ui.button_clear, &QPushButton::clicked, this, &GenerationSettingsWidget::list_clearAllOptions);
	connect(ui.button_delete, &QPushButton::clicked, this, &GenerationSettingsWidget::list_deleteSelectedOption);
	connect(ui.button_edit, &QPushButton::clicked, this, &GenerationSettingsWidget::list_editSelectedOption);
	connect(ui.button_changemode, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_changemode);
	connect(ui.button_save, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_save);
	connect(ui.button_reset, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_reset);
	connect(ui.button_selectTypeID, &QPushButton::clicked, this, &GenerationSettingsWidget::selecter_selectTypeID);
	connect(ui.button_setGenerationAmount, &QPushButton::clicked, this, &GenerationSettingsWidget::selecter_selectAmount);
}

GenerationSettingsWidget::~GenerationSettingsWidget()
{
}

void GenerationSettingsWidget::setCellFactory(SimulationModel::Cells::CellFactory* factory)
{
	this->factory = factory;
	updateOptions();
	editor_setEditMode(false);
	editor_reset();
	setButtonsStatus();
}

void GenerationSettingsWidget::setButtonsStatus(bool disabled)
{
	if (factory == nullptr) disabled = true;
	ui.button_changemode->setDisabled(disabled);
	ui.button_clear->setDisabled(disabled);
	ui.button_delete->setDisabled(disabled);
	ui.button_edit->setDisabled(disabled);
	ui.button_reset->setDisabled(disabled);
	ui.button_save->setDisabled(disabled);
	ui.button_selectTypeID->setDisabled(disabled);
	ui.button_setGenerationAmount->setDisabled(disabled);
}

void GenerationSettingsWidget::updateOptions()
{
	if (factory != nullptr) {
		auto options = factory->getOptions();
		list_setOptionsList(options);
		selecter_setOptionsList(options);
		selecter_setupGenerationAmont();
		if (editor_editmode)editor_reset();
	}
}

void GenerationSettingsWidget::generateColorSelectionEditorControls()
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

void GenerationSettingsWidget::editor_setDNAParams(CellDNA dna_options)
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

void GenerationSettingsWidget::editor_setParams(CellFactory::GenerateOption option)
{
	ui.typeIdSpinBox->setValue(option.typeID);
	editor_setDNAParams(option.dna_options);
}

CellFactory::GenerateOption GenerationSettingsWidget::editor_getParams()
{
	int typeID = ui.typeIdSpinBox->value();
	SimulationModel::Cells::CellDNA dna_options = editor_getDNAParams();
	return SimulationModel::Cells::CellFactory::GenerateOption{ dna_options,typeID };
}

CellDNA GenerationSettingsWidget::editor_getDNAParams()
{
	SimulationModel::Cells::CellDNA dna_options;
	dna_options.feed_damage = ui.feedDamageDoubleSpinBox->value();
	dna_options.max_food = ui.maxFoodDoubleSpinBox->value();
	dna_options.max_speed = ui.maxSpeedDoubleSpinBox->value();
	dna_options.detect_radius = ui.detectRadiusDoubleSpinBox->value();
	dna_options.foods_to_duplicate = ui.foodsToDuplicateDoubleSpinBox->value();
	dna_options.stoping_factor = ui.stopingFactorDoubleSpinBox->value();
	dna_options.dupl_chanse_percent = ui.duplChancePercentSpinBox->value();
	dna_options.dupl_nearsamecells_limit = ui.duplNearcellsLimitSpinBox->value();
	dna_options.foodgen_nearcells_factor = ui.foodgenNearcellsFactorDoubleSpinBox->value();
	dna_options.neardistance_calcfactor = ui.neardistanceCalcfactorDoubleSpinBox->value();
	dna_options.size = ui.sizeSpinBox->value();
	dna_options.food_generation = ui.foodGenerationDoubleSpinBox->value();

	dna_options.color = SimulationModel::Cells::CellColor(ui.colorComboBox->currentIndex());

	int index = 0;
	for (auto cellColor : SimulationModel::Cells::ALL_CELL_COLORS) {

		if (colorsBeware_checkboxes[index]->isChecked()) {
			dna_options.colors_beware.push_back(SimulationModel::Cells::CellColor(index));
		};

		if (colorsHunt_checkboxes[index]->isChecked()) {
			dna_options.colors_hunt.push_back(SimulationModel::Cells::CellColor(index));
		};

		index++;
	}

	return dna_options;
}

void GenerationSettingsWidget::selecter_setupGenerationAmont()
{
	int amount = -1;
	emit setupGenerationAmountSignal(amount);
	if (amount > -1) {
		ui.generationAmountSpinBox->setValue(amount);
	}
}

void GenerationSettingsWidget::selecter_setOptionsList(std::vector<CellFactory::GenerateOption> options)
{
	QStringList typesList;

	ui.selectTypeIDComboBox->clear();

	for (auto option : options) {
		QString typeID_Str = QString::number(option.typeID);
		bool wasAdded = false;
		for (auto type : typesList) {
			if (type == typeID_Str)wasAdded = true;
		}
		if (!wasAdded) {
			typesList.push_back(typeID_Str);
		}
	}
	typesList.sort();
	typesList.push_front(ANY_STR);

	ui.selectTypeIDComboBox->addItems(typesList);

	QString currentTypeStr = QString::number(factory->getGenerationType());
	bool isContained = typesList.contains(currentTypeStr);
	int findindex = !isContained ? 0 : typesList.indexOf(currentTypeStr);
	ui.selectTypeIDComboBox->setCurrentIndex(findindex);
}

int GenerationSettingsWidget::selecter_getSelectedIndex()
{
	QString selected_str = ui.selectTypeIDComboBox->currentText();
	return selected_str == ANY_STR ? 0 : selected_str.toInt();
}

void GenerationSettingsWidget::list_setOptionsList(std::vector<CellFactory::GenerateOption> options)
{
	ui.listWidgetOptions->clear();
	for (int index = 0; index < options.size(); index++) {
		QListWidgetItem* item = new QListWidgetItem();
		item->setBackgroundColor(ColorConverter::convertColor(options[index].dna_options.color));
		item->setTextColor(Qt::white);
		item->setText(" " + QString::number(index) + "	Type:   " + QString::number(options[index].typeID));
		ui.listWidgetOptions->addItem(item);
	}
}

int GenerationSettingsWidget::list_getSelectedIndex()
{
	return ui.listWidgetOptions->row(ui.listWidgetOptions->currentItem());
}

void GenerationSettingsWidget::editor_editOptionByID(int editId)
{
	editor_setEditId(editId);
	editor_reset();
	editor_setEditMode(true);
}

void GenerationSettingsWidget::editor_setEditId(int editId)
{
	editor_editid = editId;
	editor_updateStatusLabel();
}

void GenerationSettingsWidget::editor_setEditMode(bool editmode)
{
	bool reset = editmode == true && editor_editmode == false;
	editor_editmode = editmode;
	editor_updateStatusLabel();
	if (reset) editor_reset();
}

void GenerationSettingsWidget::editor_updateStatusLabel()
{
	if (editor_editmode) {
		ui.label_editor->setText("Editing Id <b>" + QString::number(editor_editid) + "</b>");
		ui.label_editor->setStyleSheet("background-color: lightgreen;");
	}
	else {
		ui.label_editor->setText("Creating new");
		ui.label_editor->setStyleSheet("background-color: lightskyblue;");
	}
}

void GenerationSettingsWidget::selecter_selectAmount()
{
	emit setGenerationAmountSignal(ui.generationAmountSpinBox->value());
}

void GenerationSettingsWidget::list_clearAllOptions()
{
	factory->clearOptions();
	updateOptions();
	editor_setEditId(0);
	editor_setEditMode(false);
}

void GenerationSettingsWidget::list_deleteSelectedOption()
{
	int currentDeleteIndex = list_getSelectedIndex();
	factory->deleteOption(currentDeleteIndex);
	updateOptions();
	if (editor_editid >= currentDeleteIndex) {
		if (editor_editid == currentDeleteIndex || editor_editid == 0) {
			editor_setEditId(0);
			editor_setEditMode(false);
		}
		else {
			editor_setEditId(editor_editid - 1);
			editor_reset();
		}
	}
}

void GenerationSettingsWidget::list_editSelectedOption()
{
	editor_editOptionByID(list_getSelectedIndex());
	ui.tabWidget->setCurrentIndex(2);
}

void GenerationSettingsWidget::editor_changemode()
{
	if (!editor_editmode) {
		if (editor_editid < factory->getOptions().size()) {
			editor_setEditMode(!editor_editmode);
			editor_reset();
		}
	}
	else {
		editor_setEditMode(!editor_editmode);
	}
}

void GenerationSettingsWidget::editor_reset()
{
	if (editor_editmode) {
		editor_setParams(factory->getOptions()[editor_editid]);
	}
	else {
		editor_setDNAParams(SimulationModel::Cells::CellDNA());
	}
}

void GenerationSettingsWidget::editor_save()
{
	auto option = editor_getParams();

	if (editor_editmode) {
		factory->updateOption(editor_editid, option);
	}
	else {
		factory->addOption(option);
	}
	updateOptions();
	ui.tabWidget->setCurrentIndex(1);
}

void GenerationSettingsWidget::selecter_selectTypeID()
{
	factory->setGenerationType(selecter_getSelectedIndex());
}
