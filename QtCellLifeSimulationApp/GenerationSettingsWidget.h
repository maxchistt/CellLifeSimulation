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
	void setCellFactory(SimulationModel::Cells::CellFactory* factory);
	void setButtonsStatus(bool disabled = false);

private:
	void generateColorSelectionEditorControls();
	void updateOptions();

	void selecter_setupGenerationAmont();
	void selecter_setOptionsList(std::vector<SimulationModel::Cells::CellFactory::GenerateOption> options);
	int selecter_getSelectedIndex();

	void list_setOptionsList(std::vector<SimulationModel::Cells::CellFactory::GenerateOption> options);
	int list_getSelectedIndex();

	void editor_setDNAParams(SimulationModel::Cells::CellDNA dna_options);
	void editor_setParams(SimulationModel::Cells::CellFactory::GenerateOption option);
	SimulationModel::Cells::CellFactory::GenerateOption editor_getParams();
	SimulationModel::Cells::CellDNA editor_getDNAParams();

	void editor_editOptionByID(int editId);
	void editor_setEditId(int editId);
	void editor_setEditMode(bool editmode);
	void editor_updateStatusLabel();

private slots:
	void selecter_selectTypeID();
	void selecter_selectAmount();

	void list_clearAllOptions();
	void list_deleteSelectedOption();
	void list_editSelectedOption();

	void editor_changemode();
	void editor_reset();
	void editor_save();

signals:
	void setGenerationAmountSignal(int amount);
	void setupGenerationAmountSignal(int& amount);

private:
	int editor_editid = 0;
	bool editor_editmode = false;

	std::vector<QCheckBox*> colorsBeware_checkboxes;
	std::vector<QCheckBox*> colorsHunt_checkboxes;

	SimulationModel::Cells::CellFactory* factory;
	Ui::GenerationSettingsWidget ui;
};
