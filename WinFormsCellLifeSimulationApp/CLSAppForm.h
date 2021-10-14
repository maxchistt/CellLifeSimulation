#pragma once
#include "SimulationModel.h"
#include "SimDrawController.h"

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
		Simulation* simulation;
		SimDrawController^ controller;

	private: System::Windows::Forms::ToolStripMenuItem^ timeSettingsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ speedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ plusSpeed_toolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ minusSpeed_ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ qualityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ plusQuality_toolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ resetTimeSettings_ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ minusQuality_ToolStripMenuItem;

	public:

		void OnInitMainForm();

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


	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ actionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ generateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem_add10;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem_add30;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem_add70;
	private: System::Windows::Forms::ToolStripMenuItem^ clearToolStripMenuItem_Clear;
	private: System::Windows::Forms::ToolStripMenuItem^ playPauseToolStripMenuItem;









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
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->actionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->generateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem_add10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem_add30 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem_add70 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem_Clear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playPauseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timeSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->speedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plusSpeed_toolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->minusSpeed_ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->qualityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plusQuality_toolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->minusQuality_ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetTimeSettings_ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(0, 30);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(582, 323);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->SizeChanged += gcnew System::EventHandler(this, &CLSAppForm::image_resize);
			// 
			// timer
			// 
			this->timer->Interval = 200;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->actionsToolStripMenuItem,
					this->playPauseToolStripMenuItem, this->timeSettingsToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(582, 30);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// actionsToolStripMenuItem
			// 
			this->actionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->generateToolStripMenuItem,
					this->clearToolStripMenuItem_Clear
			});
			this->actionsToolStripMenuItem->Name = L"actionsToolStripMenuItem";
			this->actionsToolStripMenuItem->Size = System::Drawing::Size(72, 26);
			this->actionsToolStripMenuItem->Text = L"Actions";
			// 
			// generateToolStripMenuItem
			// 
			this->generateToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem_add10,
					this->toolStripMenuItem_add30, this->toolStripMenuItem_add70
			});
			this->generateToolStripMenuItem->Name = L"generateToolStripMenuItem";
			this->generateToolStripMenuItem->Size = System::Drawing::Size(152, 26);
			this->generateToolStripMenuItem->Text = L"Generate";
			// 
			// toolStripMenuItem_add10
			// 
			this->toolStripMenuItem_add10->Name = L"toolStripMenuItem_add10";
			this->toolStripMenuItem_add10->Size = System::Drawing::Size(108, 26);
			this->toolStripMenuItem_add10->Text = L"10";
			this->toolStripMenuItem_add10->Click += gcnew System::EventHandler(this, &CLSAppForm::toolStripMenuItem_add10_Click);
			// 
			// toolStripMenuItem_add30
			// 
			this->toolStripMenuItem_add30->Name = L"toolStripMenuItem_add30";
			this->toolStripMenuItem_add30->Size = System::Drawing::Size(108, 26);
			this->toolStripMenuItem_add30->Text = L"30";
			this->toolStripMenuItem_add30->Click += gcnew System::EventHandler(this, &CLSAppForm::toolStripMenuItem_add30_Click);
			// 
			// toolStripMenuItem_add70
			// 
			this->toolStripMenuItem_add70->Name = L"toolStripMenuItem_add70";
			this->toolStripMenuItem_add70->Size = System::Drawing::Size(108, 26);
			this->toolStripMenuItem_add70->Text = L"70";
			this->toolStripMenuItem_add70->Click += gcnew System::EventHandler(this, &CLSAppForm::toolStripMenuItem_add70_Click);
			// 
			// clearToolStripMenuItem_Clear
			// 
			this->clearToolStripMenuItem_Clear->Name = L"clearToolStripMenuItem_Clear";
			this->clearToolStripMenuItem_Clear->Size = System::Drawing::Size(152, 26);
			this->clearToolStripMenuItem_Clear->Text = L"Clear";
			this->clearToolStripMenuItem_Clear->Click += gcnew System::EventHandler(this, &CLSAppForm::clearToolStripMenuItem_Clear_Click);
			// 
			// playPauseToolStripMenuItem
			// 
			this->playPauseToolStripMenuItem->Name = L"playPauseToolStripMenuItem";
			this->playPauseToolStripMenuItem->Size = System::Drawing::Size(93, 26);
			this->playPauseToolStripMenuItem->Text = L"Play/Pause";
			this->playPauseToolStripMenuItem->Click += gcnew System::EventHandler(this, &CLSAppForm::playPauseToolStripMenuItem_Click);
			// 
			// timeSettingsToolStripMenuItem
			// 
			this->timeSettingsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->speedToolStripMenuItem,
					this->qualityToolStripMenuItem, this->resetTimeSettings_ToolStripMenuItem
			});
			this->timeSettingsToolStripMenuItem->Name = L"timeSettingsToolStripMenuItem";
			this->timeSettingsToolStripMenuItem->Size = System::Drawing::Size(111, 26);
			this->timeSettingsToolStripMenuItem->Text = L"Time settings";
			// 
			// speedToolStripMenuItem
			// 
			this->speedToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->plusSpeed_toolStripMenuItem,
					this->minusSpeed_ToolStripMenuItem
			});
			this->speedToolStripMenuItem->Name = L"speedToolStripMenuItem";
			this->speedToolStripMenuItem->Size = System::Drawing::Size(139, 26);
			this->speedToolStripMenuItem->Text = L"Speed";
			// 
			// plusSpeed_toolStripMenuItem
			// 
			this->plusSpeed_toolStripMenuItem->Name = L"plusSpeed_toolStripMenuItem";
			this->plusSpeed_toolStripMenuItem->Size = System::Drawing::Size(102, 26);
			this->plusSpeed_toolStripMenuItem->Text = L"+";
			this->plusSpeed_toolStripMenuItem->Click += gcnew System::EventHandler(this, &CLSAppForm::plusSpeed_toolStripMenuItem_Click);
			// 
			// minusSpeed_ToolStripMenuItem
			// 
			this->minusSpeed_ToolStripMenuItem->Name = L"minusSpeed_ToolStripMenuItem";
			this->minusSpeed_ToolStripMenuItem->Size = System::Drawing::Size(102, 26);
			this->minusSpeed_ToolStripMenuItem->Text = L"-";
			this->minusSpeed_ToolStripMenuItem->Click += gcnew System::EventHandler(this, &CLSAppForm::minusSpeed_ToolStripMenuItem_Click);
			// 
			// qualityToolStripMenuItem
			// 
			this->qualityToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->plusQuality_toolStripMenuItem,
					this->minusQuality_ToolStripMenuItem
			});
			this->qualityToolStripMenuItem->Name = L"qualityToolStripMenuItem";
			this->qualityToolStripMenuItem->Size = System::Drawing::Size(139, 26);
			this->qualityToolStripMenuItem->Text = L"Quality";
			// 
			// plusQuality_toolStripMenuItem
			// 
			this->plusQuality_toolStripMenuItem->Name = L"plusQuality_toolStripMenuItem";
			this->plusQuality_toolStripMenuItem->Size = System::Drawing::Size(102, 26);
			this->plusQuality_toolStripMenuItem->Text = L"+";
			this->plusQuality_toolStripMenuItem->Click += gcnew System::EventHandler(this, &CLSAppForm::plusQuality_toolStripMenuItem_Click);
			// 
			// minusQuality_ToolStripMenuItem
			// 
			this->minusQuality_ToolStripMenuItem->Name = L"minusQuality_ToolStripMenuItem";
			this->minusQuality_ToolStripMenuItem->Size = System::Drawing::Size(102, 26);
			this->minusQuality_ToolStripMenuItem->Text = L"-";
			this->minusQuality_ToolStripMenuItem->Click += gcnew System::EventHandler(this, &CLSAppForm::minusQuality_ToolStripMenuItem_Click);
			// 
			// resetTimeSettings_ToolStripMenuItem
			// 
			this->resetTimeSettings_ToolStripMenuItem->Name = L"resetTimeSettings_ToolStripMenuItem";
			this->resetTimeSettings_ToolStripMenuItem->Size = System::Drawing::Size(139, 26);
			this->resetTimeSettings_ToolStripMenuItem->Text = L"Reset";
			this->resetTimeSettings_ToolStripMenuItem->Click += gcnew System::EventHandler(this, &CLSAppForm::resetTimeSettings_ToolStripMenuItem_Click);
			// 
			// CLSAppForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 17);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 353);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"CLSAppForm";
			this->Text = L"Cell Life Simulation";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void image_resize(System::Object^ sender, System::EventArgs^ e);
	private: System::Void toolStripMenuItem_add10_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void toolStripMenuItem_add30_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void toolStripMenuItem_add70_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void clearToolStripMenuItem_Clear_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void playPauseToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void plusSpeed_toolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void minusSpeed_ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void plusQuality_toolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void minusQuality_ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void resetTimeSettings_ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
