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
	void updateTable();
	void prepareColorSelections();
	void setEditorDNAParams(SimulationModel::Cells::CellDNA dna_options);
	void setEditorParams(SimulationModel::Cells::Genera)

private slots:
	void clearAllOptions();
	void deleteSelectedOption();
	void editSelectedOption();
	void editor_new();
	void editor_reset();
	void editor_save();

private:
	std::vector<QCheckBox*> colorsBeware_checkboxes;
	std::vector<QCheckBox*> colorsHunt_checkboxes;
	SimulationModel::Cells::CellFactory* factory;
	Ui::GenerationSettingsWidget ui;
};
