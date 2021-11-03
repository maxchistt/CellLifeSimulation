#include "TimeSettingsDialog.h"

TimeSettingsDialog::TimeSettingsDialog(QWidget* parent, SimulationController* controller)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->controller = controller;
	setupParams();
}

TimeSettingsDialog::~TimeSettingsDialog()
{
}

void TimeSettingsDialog::setupParams()
{
	float timelapse_res;
	int interval_res;
	controller->getTimeSettings(&interval_res, &timelapse_res);

	int fps = 1000 / interval_res;
	if (fps > ui.fpsSlider->maximum())fps = ui.fpsSlider->maximum();
	ui.fpsSlider->setValue(fps);

	int timelapse = static_cast<int>(timelapse_res);
	if (timelapse <= 0)timelapse = 1;
	ui.timelapseSlider->setValue(timelapse);
}

void TimeSettingsDialog::applySettings()
{
	int fps = this->ui.fpsSlider->value();
	int timelapse = this->ui.timelapseSlider->value();
	controller->setTimeSettings(1000 / fps, timelapse);
}

void TimeSettingsDialog::accept()
{
	if (controller != Q_NULLPTR) {
		applySettings();
		this->QDialog::accept();
	}
	else {
		this->QDialog::reject();
	}
}
