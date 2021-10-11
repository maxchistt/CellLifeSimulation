#include "CLSAppForm.h"
#include "SimulationModel.h"

using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;

void CLSAppForm::OnInitMainForm()
{
	controller = gcnew SimDrawController(new Simulation(), this->pictureBox, this->timer);
	controller->setTimeSettings(200, 5);
	//controller->start();
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

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::startToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->start();
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::pauseToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->stop();
}


