#include "GenerationSettingsWidget.h"
#include "ColorConverter.h"
#include <QListWidgetItem>

GenerationSettingsWidget::GenerationSettingsWidget(QWidget* parent, SimulationModel::Cells::CellFactory* factory)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFactory(factory);
	updateOptionsList();
	ui.tabWidget->setCurrentIndex(0);
	prepareColorSelections();
	setEditorMode(false);
	editor_reset();

	connect(ui.button_clear, &QPushButton::clicked, this, &GenerationSettingsWidget::clearAllOptions);
	connect(ui.button_delete, &QPushButton::clicked, this, &GenerationSettingsWidget::deleteSelectedOption);
	connect(ui.button_edit, &QPushButton::clicked, this, &GenerationSettingsWidget::editSelectedOption);
	connect(ui.button_changemode, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_changemode);
	connect(ui.button_save, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_save);
	connect(ui.button_reset, &QPushButton::clicked, this, &GenerationSettingsWidget::editor_reset);
	connect(ui.button_selectTypeID, &QPushButton::clicked, this, &GenerationSettingsWidget::selectTypeID);
}

GenerationSettingsWidget::~GenerationSettingsWidget()
{
}

void GenerationSettingsWidget::setFactory(SimulationModel::Cells::CellFactory* factory)
{
	this->factory = factory;
}

void GenerationSettingsWidget::updateOptionsList()
{
	int index = 0;
	std::vector<int> typesInList;
	ui.listWidgetOptions->clear();
	ui.selectTypeIDComboBox->clear();
	ui.selectTypeIDComboBox->addItem("Any");
	for (auto option : factory->getOptions()) {
		auto color = ColorConverter::convertColor(option.dna_options.color);
		QListWidgetItem* item = new QListWidgetItem();
		item->setBackgroundColor(color);
		item->setTextColor(Qt::white);
		item->setText(" " + QString::number(index) + "	Type:   " + QString::number(option.typeID));
		ui.listWidgetOptions->addItem(item);

		bool wasAdded = false;
		for (auto type : typesInList) {
			if (type == option.typeID)wasAdded = true;
		}
		if (!wasAdded) {
			typesInList.push_back(option.typeID);
		}

		index++;
	}

	std::sort(typesInList.begin(), typesInList.end());
	bool isContained = false;
	for (auto typeID : typesInList) {
		ui.selectTypeIDComboBox->addItem(QString::number(typeID));
		if (typeID == factory->getGenerationType())isContained = true;
	}
	int findindex = factory->getGenerationType() == 0 || !isContained ? 0 : ui.selectTypeIDComboBox->findText(QString::number(factory->getGenerationType()));
	ui.selectTypeIDComboBox->setCurrentIndex(findindex);
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

void GenerationSettingsWidget::setEditorParams(SimulationModel::Cells::CellFactory::GenerateOption option)
{
	ui.typeIdSpinBox->setValue(option.typeID);
	setEditorDNAParams(option.dna_options);
}

void GenerationSettingsWidget::setEditorMode(bool editmode)
{
	edit_editmode = editmode;
	if (edit_editmode) {
		ui.label_editor->setText("Editing Id <b>" + QString::number(edit_id) + "</b>");
		ui.label_editor->setStyleSheet("background-color: lightgreen;");
	}
	else {
		ui.label_editor->setText("Creating new");
		ui.label_editor->setStyleSheet("background-color: lightskyblue;");
	}
}

SimulationModel::Cells::CellFactory::GenerateOption GenerationSettingsWidget::getOptionFromControls()
{
	int typeID = ui.typeIdSpinBox->value();
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

	return SimulationModel::Cells::CellFactory::GenerateOption{ dna_options,typeID };
}

void GenerationSettingsWidget::clearAllOptions()
{
	factory->clearOptions();
	updateOptionsList();
}

void GenerationSettingsWidget::deleteSelectedOption()
{
	int currentindex = ui.listWidgetOptions->row(ui.listWidgetOptions->currentItem());
	factory->deleteOption(currentindex);
	updateOptionsList();
	setEditorMode(false);
}

void GenerationSettingsWidget::editSelectedOption()
{
	edit_id = ui.listWidgetOptions->row(ui.listWidgetOptions->currentItem());

	setEditorParams(factory->getOptions()[edit_id]);
	setEditorMode(true);

	ui.tabWidget->setCurrentIndex(2);
}

void GenerationSettingsWidget::editor_changemode()
{
	setEditorMode(!edit_editmode);
	if (edit_editmode) {
		auto options = factory->getOptions();
		if (edit_id < options.size()) {
			setEditorParams(options[edit_id]);
		}
		else {
			setEditorMode(!edit_editmode);
		}
	}
}

void GenerationSettingsWidget::editor_reset()
{
	if (edit_editmode) {
		setEditorParams(factory->getOptions()[edit_id]);
	}
	else {
		setEditorDNAParams(SimulationModel::Cells::CellDNA());
	}
}

void GenerationSettingsWidget::editor_save()
{
	auto option = getOptionFromControls();

	if (edit_editmode) {
		factory->updateOption(edit_id, option);
	}
	else {
		factory->addOption(option);
	}
	setEditorMode(false);
	updateOptionsList();
	ui.tabWidget->setCurrentIndex(1);
}

void GenerationSettingsWidget::selectTypeID()
{
	auto str = ui.selectTypeIDComboBox->currentText();
	factory->setGenerationType(str == "Any" ? 0 : str.toInt());
}
