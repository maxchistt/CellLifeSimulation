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
	/// ������ ��� CLSAppForm
	/// </summary>
	public ref class CLSAppForm : public System::Windows::Forms::Form
	{
	private:
		SimDrawController^ controller;
		
	public:

		void OnInitMainForm();
		
		CLSAppForm(void)
		{
			InitializeComponent();
			OnInitMainForm();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~CLSAppForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox;

	private: System::Windows::Forms::Button^ button_generate;

	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
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

	private: System::Void button_generate_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
