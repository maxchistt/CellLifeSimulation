#include "CLSAppForm.h"

namespace WinFormsCellLifeSimulationApp {
	[STAThreadAttribute]
	void main(array<String^>^ args) {
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		CLSAppForm form;
		Application::Run(% form);
	}
}