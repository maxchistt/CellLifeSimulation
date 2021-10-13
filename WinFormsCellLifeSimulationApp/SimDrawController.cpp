#include "SimDrawController.h"
#include "CLSAppForm.h"

using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;


void SimDrawController::setTimeSettings(int interval, int timelapse)
{
	sim->setTimelapse(timelapse);
	timer->Interval = interval;
}

void SimDrawController::start()
{
	timer->Start();
}

void SimDrawController::stop()
{
	timer->Stop();
}

bool WinFormsCellLifeSimulationApp::SimDrawController::timerEnabled()
{
	return timer->Enabled;
}

void SimDrawController::clear()
{
	delete sim;
	sim = new SimulationModel::Simulation();
	fitSimSize();
	if (!timer->Enabled)redraw();
}

void SimDrawController::generateCells()
{
	sim->generateCells();
}

void SimDrawController::generateCells(int n)
{
	sim->generateCells(n);
	if (!timer->Enabled)redraw();
}

void SimDrawController::redraw()
{
	if (sim != nullptr)  draw(sim->drawSimulation());
}

void SimDrawController::connectTimer()
{
	timer->Tick += gcnew EventHandler(this, &SimDrawController::tick);
}

System::Void SimDrawController::tick(System::Object^ sender, System::EventArgs^ e)
{
	redraw();
}

SimDrawController::SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox, Windows::Forms::Timer^ timer)
{
	this->sim = sim;
	this->pictureBox = pictureBox;
	this->timer = timer;
	fitSimSize();
	connectTimer();
	//setTimeSettings(200, 5);
	//start();
}

SimDrawController::SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox)
	: SimDrawController(sim, pictureBox, gcnew Timer()) {};

Drawing::Color SimDrawController::convertColor(SimulationModel::Cells::CellColor cell_color)
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

void SimDrawController::draw(std::vector<SimulationModel::drawEntity> entities)
{
	try {
		auto bmp = gcnew Bitmap(this->sim->fieldSize.x, this->sim->fieldSize.y);
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
			graph->DrawImage(bmp1, Drawing::Point(ent.point.x - ent.size / 2, ent.point.y - ent.size / 2));
		}
		this->pictureBox->Image = bmp;
		this->pictureBox->Invalidate();
		this->pictureBox->Refresh();
	}
	catch (System::Object^ sender) {
		throw - 1;
	};
}

void SimDrawController::fitSimSize()
{
	if (sim != nullptr)sim->setSize(pictureBox->Size.Width, pictureBox->Size.Height);
}
