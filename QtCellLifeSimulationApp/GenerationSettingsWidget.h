#pragma once

#include <QWidget>
#include "ui_GenerationSettingsWidget.h"
#include "SimulationModel.h"
#include <QCheckbox>

class GenerationSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	GenerationSettingsWidget(QWidget* parent = Q_NULLPTR, SimulationModel::Cells::CellFactory* factory = nullptr);
	~GenerationSettingsWidget();
	void setFactory(SimulationModel::Cells::CellFactory* factory);
private:
	void updateOptionsList();
	void prepareColorSelections();
	void setEditorDNAParams(SimulationModel::Cells::CellDNA dna_options);
	void setEditorParams(SimulationModel::Cells::CellFactory::GenerateOption option);
	void setEditorModeAndUpdLabel(bool editmode);
	SimulationModel::Cells::CellFactory::GenerateOption getOptionFromControls();

private slots:
	void clearAllOptions();
	void deleteSelectedOption();
	void editSelectedOption();
	void editor_changemode();
	void editor_reset();
	void editor_save();
	void selectTypeID();

private:
	int edit_id = 0;
	bool edit_editmode = false;
	std::vector<QCheckBox*> colorsBeware_checkboxes;
	std::vector<QCheckBox*> colorsHunt_checkboxes;
	SimulationModel::Cells::CellFactory* factory;
	Ui::GenerationSettingsWidget ui;
};
