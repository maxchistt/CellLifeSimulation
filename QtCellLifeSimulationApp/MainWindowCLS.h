#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindowCLS.h"
#include "SimulationModel.h"
#include "SimulationView.h"
#include "SimulationTimeController.h"
#include "SimulationViewController.h"
#include "GenerationSettingsWidget.h"
#include <QCloseEvent>

class MainWindowCLS : public QMainWindow
{
	Q_OBJECT
public:
	MainWindowCLS(QWidget* parent = Q_NULLPTR);
	~MainWindowCLS();
private:
	GenerationSettingsWidget* generationSettingsWidget;
	SimulationModel::Simulation* model;
	SimulationView* view;
	SimulationTimeController* controller_time;
	SimulationViewController* controller_view;
	Ui::MainWindowCLS ui;
	void setPlayPause(bool on);
private slots:
	void onPlayPause();
	void onGenerate();
	void onClear();
	void onLimitSettings();
	void onGenerationSettings();
	void onTimeSettings();
	void about();
	void aboutQt();
	void MainWindowCLS::closeEvent(QCloseEvent* event);
};