#include "CLSAppForm.h"
#include "SimulationModel.h"

using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;

void CLSAppForm::OnInitMainForm()
{
	simulation = new Simulation();
	controller = gcnew SimDrawController(this->simulation, this->pictureBox, this->timer);
	controller->setTimeSettings(20, 5);
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


