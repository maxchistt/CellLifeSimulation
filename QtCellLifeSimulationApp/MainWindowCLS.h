#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindowCLS.h"
#include "SimulationModel.h"
#include "SimulationView.h"
#include "SimulationController.h"
#include "GenerationSettingsWidget.h"
#include <QCloseEvent>

class MainWindowCLS : public QMainWindow
{
	Q_OBJECT
public:
	MainWindowCLS(QWidget* parent = Q_NULLPTR);
	~MainWindowCLS();
private:
	GenerationSettingsWidget* generationSettings;
	SimulationModel::Simulation* model;
	SimulationView* view;
	SimulationController* controller;
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
