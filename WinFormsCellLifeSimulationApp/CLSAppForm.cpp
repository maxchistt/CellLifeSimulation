#include "CLSAppForm.h"
using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;

Drawing::Color CLSAppForm::convertColor(SimulationModel::Cells::CellColor cell_color)
{
	Drawing::Color color;
	switch (cell_color)
	{
	case Cells::CellColor::BLUE:
		color = Drawing::Color::Blue;
		break;
	case Cells::CellColor::BROWN:
		color = Drawing::Color::Brown;
		break;
	case Cells::CellColor::GRAY:
		color = Drawing::Color::Gray;
		break;
	case Cells::CellColor::GREEN:
		color = Drawing::Color::Green;
		break;
	case Cells::CellColor::ORANGE:
		color = Drawing::Color::Orange;
		break;
	case Cells::CellColor::RED:
		color = Drawing::Color::Red;
		break;
	case Cells::CellColor::YELLOW:
		color = Drawing::Color::Yellow;
		break;
	default:
		color = Drawing::Color::Black;
		break;
	}
	return color;
}

void CLSAppForm::OnInitMainForm()
{
	sim = new Simulation(pictureBox->Size.Width, pictureBox->Size.Height);
	timer1->Start();
}

void CLSAppForm::draw(Windows::Forms::PictureBox^ pictureBox, std::vector<SimulationModel::drawEntity> entities)
{
	auto bmp = gcnew Bitmap(sim->fieldSize.x, sim->fieldSize.y);
	auto graph = Graphics::FromImage(bmp);

	for each (drawEntity ent in entities)
	{

		auto bmp1 = gcnew System::Drawing::Bitmap(ent.size, ent.size);
		auto color = convertColor(ent.color);

		for (int i = 0; i < ent.size; i++) {
			for (int j = 0; j < ent.size; j++) {
				if (sqrt(pow(j - ent.size / 2, 2) + pow(i - ent.size / 2, 2)) < ent.size / 2) {
					bmp1->SetPixel(i, j, color);
				}

			}
		}


		graph->DrawImage(bmp1, Drawing::Point(ent.point.x- ent.size / 2, ent.point.y - ent.size / 2));
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

System::Void WinFormsCellLifeSimulationApp::CLSAppForm::button_generate_Click(System::Object^ sender, System::EventArgs^ e)
{
	sim->generateCells();
}


