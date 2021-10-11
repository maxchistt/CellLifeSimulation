#include "CLSAppForm.h"
using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;

void CLSAppForm::OnInitMainForm()
{
	sim = new Simulation(pictureBox->Size.Width, pictureBox->Size.Height);
	//redraw();
	timer1->Start();
}

void CLSAppForm::draw(Windows::Forms::PictureBox^ pictureBox, std::vector<SimulationModel::drawEntity> entities)
{
	auto bmp = gcnew Bitmap(sim->fieldSize.x, sim->fieldSize.y);
	auto graph = Graphics::FromImage(bmp);

	for each (drawEntity ent in entities)
	{

		auto bmp1 = gcnew System::Drawing::Bitmap(ent.size, ent.size);


		for (int i = 0; i < ent.size; i++) {
			for (int j = 0; j < ent.size; j++) {
				bmp1->SetPixel(i, j, Drawing::Color::DarkGreen);
			}
		}


		graph->DrawImage(bmp1, Drawing::Point(ent.point.x, ent.point.y));


	}

	pictureBox->Image = bmp;
	pictureBox->Invalidate();
	pictureBox->Refresh();
}

void CLSAppForm::redraw()
{
	if (sim != nullptr) { 
		draw(pictureBox, sim->drawSimulation()); 
	}
}

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	redraw();
}


