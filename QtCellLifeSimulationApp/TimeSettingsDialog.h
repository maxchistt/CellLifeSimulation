#pragma once

#include <QDialog>
#include "ui_TimeSettingsDialog.h"
#include "SimulationTimeController.h"

class TimeSettingsDialog : public QDialog
{
	Q_OBJECT

public:
	TimeSettingsDialog(QWidget* parent, SimulationTimeController* controller);
	~TimeSettingsDialog();

private:
	SimulationTimeController* controller;
	Ui::TimeSettingsDialog ui;
	void setupParams();
	void applySettings();
private slots:
	void accept();
};
