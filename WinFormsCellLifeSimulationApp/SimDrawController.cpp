#include "SimDrawController.h"
#include "CLSAppForm.h"

using namespace WinFormsCellLifeSimulationApp;
using namespace SimulationModel;


void SimDrawController::time_setTimeSettings(int interval, float timelapse)
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
	sim->clearAll();
	if (!timer->Enabled)redraw();
}

void SimDrawController::generateCells()
{
	cellFactory()->generateCells();
}

void SimDrawController::generateCells(int n)
{
	cellFactory()->generateCells(n);
	if (!timer->Enabled)redraw();
}

void SimDrawController::time_changeQuality(float factor)
{
	if (factor == 0 || factor == 1)return;
	if (factor < 0)factor = 1.0 / -factor;
	auto oldInt = timer->Interval;
	try {
		timer->Interval /= factor;
		sim->timelapse *= factor;
	}
	catch (Exception^ e) {
		catchException(e);
		timer->Interval = oldInt;
	};
}

void SimDrawController::time_changeTimerSpeed(float factor)
{
	if (factor == 0 || factor == 1)return;
	if (factor < 0)factor = 1.0 / -factor;
	auto oldInt = timer->Interval;
	try {
		timer->Interval /= factor;
	}
	catch (Exception^ e) {
		catchException(e);
		timer->Interval = oldInt;
	};
}

void SimDrawController::setCellsLimit(int cellslimit)
{
	if (cellslimit > 0)sim->cellsLimit = cellslimit;
}

void SimDrawController::setGenerationType(int type)
{
	cellFactory()->setGenerationType(type);
}

void SimDrawController::redraw()
{
	if (sim != nullptr)  draw(sim->getNextFrame());
}

void SimDrawController::connectTimer()
{
	timer->Tick += gcnew EventHandler(this, &SimDrawController::tick);
}

System::Void SimDrawController::tick(System::Object^ sender, System::EventArgs^ e)
{
	redraw();
}

void WinFormsCellLifeSimulationApp::SimDrawController::catchException(Exception^ e)
{
	this->pictureBox->Parent->Text = header + "  Error: " + e->Message;
}

SimDrawController::SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox, Windows::Forms::Timer^ timer)
{
	this->sim = sim;
	this->pictureBox = pictureBox;
	this->timer = timer;
	fitSimSize();
	connectTimer();
	header = this->pictureBox->Parent->Text;
}

SimDrawController::SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox)
	: SimDrawController(sim, pictureBox, gcnew Timer()) {};

Cells::CellFactory* SimDrawController::cellFactory()
{
	return sim->cellFactory;
}

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
	catch (Exception^ e) {
		catchException(e);
	};
}

void SimDrawController::fitSimSize()
{
	if (sim != nullptr && pictureBox->Size.Width > 0 && pictureBox->Size.Height > 0) {
		sim->setSize(pictureBox->Size.Width, pictureBox->Size.Height);
	}
}
