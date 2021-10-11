#pragma once
#include "SimulationModel.h"

namespace WinFormsCellLifeSimulationApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ CLSAppForm
	/// </summary>
	public ref class CLSAppForm : public System::Windows::Forms::Form
	{
	private:
		SimulationModel::Simulation* sim = nullptr;
		Drawing::Color convertColor(SimulationModel::Cells::CellColor cell_color);
	public:

		void OnInitMainForm();
		void draw(Windows::Forms::PictureBox^ pictureBox, std::vector<SimulationModel::drawEntity> entities);
		void redraw();
		CLSAppForm(void)
		{
			InitializeComponent();
			OnInitMainForm();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~CLSAppForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button_generate;

	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button_generate = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(12, 9);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1028, 572);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &CLSAppForm::timer1_Tick);
			// 
			// button_generate
			// 
			this->button_generate->Location = System::Drawing::Point(815, 74);
			this->button_generate->Name = L"button_generate";
			this->button_generate->Size = System::Drawing::Size(109, 48);
			this->button_generate->TabIndex = 1;
			this->button_generate->Text = L"generate";
			this->button_generate->UseVisualStyleBackColor = true;
			this->button_generate->Click += gcnew System::EventHandler(this, &CLSAppForm::button_generate_Click);
			// 
			// CLSAppForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1052, 593);
			this->Controls->Add(this->button_generate);
			this->Controls->Add(this->pictureBox);
			this->Name = L"CLSAppForm";
			this->Text = L"CLSAppForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_generate_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
