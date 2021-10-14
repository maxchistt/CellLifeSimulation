#include "CLSAppForm.h"
#include "SimulationModel.h"
#define SETTINGS_TIMER_MS			30
#define SETTINGS_TIMELAPSE_PARAM	20
#define SETTINGS_CELLS_LIMIT		300

using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;

void CLSAppForm::OnInitMainForm()
{
	simulation = new Simulation();
	controller = gcnew SimDrawController(this->simulation, this->pictureBox, this->timer);
	controller->time_setTimeSettings(SETTINGS_TIMER_MS, SETTINGS_TIMELAPSE_PARAM);
	controller->setCellsLimit(SETTINGS_CELLS_LIMIT);
	this->playPauseToolStripMenuItem->Text = L"Play";
}

System::Void CLSAppForm::image_resize(System::Object^ sender, System::EventArgs^ e)
{
	if (controller != nullptr)controller->fitSimSize();
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::toolStripMenuItem_add10_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->generateCells(10);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::toolStripMenuItem_add30_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->generateCells(30);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::toolStripMenuItem_add70_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->generateCells(70);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::clearToolStripMenuItem_Clear_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->clear();
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::playPauseToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (controller->timerEnabled()) {
		controller->stop();
		this->playPauseToolStripMenuItem->Text = L"Play";
	}
	else {
		controller->start();
		this->playPauseToolStripMenuItem->Text = L"Pause";
	}
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::plusSpeed_toolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->time_changeTimerSpeed(1.5);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::minusSpeed_ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->time_changeTimerSpeed(-1.5);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::plusQuality_toolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->time_changeQuality(1.5);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::minusQuality_ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->time_changeQuality(-1.5);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::resetTimeSettings_ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->time_setTimeSettings(SETTINGS_TIMER_MS, SETTINGS_TIMELAPSE_PARAM);
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::setGenerationType_ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	auto selectedType = this->generationType_toolStripComboBox->SelectedIndex;
	this->controller->setGenerationType(selectedType);
}


