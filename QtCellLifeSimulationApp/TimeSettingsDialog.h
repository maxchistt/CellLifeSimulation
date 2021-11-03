#pragma once

#include <QDialog>
#include "ui_TimeSettingsDialog.h"
#include "SimulationController.h"

class TimeSettingsDialog : public QDialog
{
	Q_OBJECT

public:
	TimeSettingsDialog(QWidget* parent, SimulationController* controller);
	~TimeSettingsDialog();

private:
	SimulationController* controller;
	Ui::TimeSettingsDialog ui;
	void setupParams();
	void applySettings();
private slots:
	void accept();
};
