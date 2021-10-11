#include "CLSAppForm.h"
#include "SimulationModel.h"

using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;

void CLSAppForm::OnInitMainForm()
{
	controller = gcnew SimDrawController(new Simulation(), this->pictureBox,this->timer);
	controller->setTimeSettings(200, 5);
	controller->start();
}

System::Void CLSAppForm::button_generate_Click(System::Object^ sender, System::EventArgs^ e)
{
	controller->generateCells();
}


