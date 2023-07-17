#pragma once
#include "SurveillanceSystem.h"
#include "ServerIO.h"
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
using namespace msclr::interop;

namespace POO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for modifySurvSis
	/// </summary>
	public ref class modifySurvSis : public System::Windows::Forms::Form
	{
	public:
		SurveillanceSystem^ survSys;
		modifySurvSis(void)
		{
			InitializeComponent();
			this->RecordStatusCB->Checked = survSys->getIsRecording();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

		modifySurvSis(SurveillanceSystem^% ss)
		{
			InitializeComponent();
			survSys = ss;
			this->RecordStatusCB->Checked = survSys->getIsRecording();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~modifySurvSis()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ SensitivityTB;
	protected:

	protected:

	protected:

	protected:
	private: Bunifu::Framework::UI::BunifuThinButton2^ SaveButton;
	private: System::Windows::Forms::Label^ labelSensitivity;
	private: System::Windows::Forms::CheckBox^ RecordStatusCB;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(modifySurvSis::typeid));
			this->SensitivityTB = (gcnew System::Windows::Forms::TextBox());
			this->SaveButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->labelSensitivity = (gcnew System::Windows::Forms::Label());
			this->RecordStatusCB = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// SensitivityTB
			// 
			this->SensitivityTB->BackColor = System::Drawing::Color::Gainsboro;
			this->SensitivityTB->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SensitivityTB->Location = System::Drawing::Point(40, 58);
			this->SensitivityTB->Margin = System::Windows::Forms::Padding(4);
			this->SensitivityTB->Name = L"SensitivityTB";
			this->SensitivityTB->Size = System::Drawing::Size(190, 39);
			this->SensitivityTB->TabIndex = 37;
			// 
			// SaveButton
			// 
			this->SaveButton->ActiveBorderThickness = 1;
			this->SaveButton->ActiveCornerRadius = 20;
			this->SaveButton->ActiveFillColor = System::Drawing::Color::Black;
			this->SaveButton->ActiveForecolor = System::Drawing::Color::White;
			this->SaveButton->ActiveLineColor = System::Drawing::Color::Black;
			this->SaveButton->BackColor = System::Drawing::SystemColors::Control;
			this->SaveButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SaveButton.BackgroundImage")));
			this->SaveButton->ButtonText = L"Save";
			this->SaveButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->SaveButton->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SaveButton->ForeColor = System::Drawing::Color::Black;
			this->SaveButton->IdleBorderThickness = 1;
			this->SaveButton->IdleCornerRadius = 20;
			this->SaveButton->IdleFillColor = System::Drawing::Color::White;
			this->SaveButton->IdleForecolor = System::Drawing::Color::Black;
			this->SaveButton->IdleLineColor = System::Drawing::Color::Black;
			this->SaveButton->Location = System::Drawing::Point(72, 217);
			this->SaveButton->Margin = System::Windows::Forms::Padding(5);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(129, 55);
			this->SaveButton->TabIndex = 41;
			this->SaveButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->SaveButton->Click += gcnew System::EventHandler(this, &modifySurvSis::SaveButton_Click);
			// 
			// labelSensitivity
			// 
			this->labelSensitivity->AutoSize = true;
			this->labelSensitivity->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelSensitivity->Location = System::Drawing::Point(84, 26);
			this->labelSensitivity->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelSensitivity->Name = L"labelSensitivity";
			this->labelSensitivity->Size = System::Drawing::Size(101, 28);
			this->labelSensitivity->TabIndex = 39;
			this->labelSensitivity->Text = L"Sensitivity";
			// 
			// RecordStatusCB
			// 
			this->RecordStatusCB->AutoSize = true;
			this->RecordStatusCB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->RecordStatusCB->Location = System::Drawing::Point(58, 133);
			this->RecordStatusCB->Name = L"RecordStatusCB";
			this->RecordStatusCB->Size = System::Drawing::Size(157, 29);
			this->RecordStatusCB->TabIndex = 42;
			this->RecordStatusCB->Text = L"Record Status";
			this->RecordStatusCB->UseVisualStyleBackColor = true;
			// 
			// modifySurvSis
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(271, 299);
			this->Controls->Add(this->RecordStatusCB);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->labelSensitivity);
			this->Controls->Add(this->SensitivityTB);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"modifySurvSis";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"modifySurvSis";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	bool IsDigitsOnly(String^ str)
	{
		for each (Char c in str)
		{
			if (!Char::IsDigit(c))
			{
				return false;
			}
		}
		return true;
	}

	bool IsFirstDigitNonZero(String^ str)
	{
		if (str->Length == 0 || str->Length > 2)
		{
			return false;
		}

		Char firstChar = str[0];
		if (!Char::IsDigit(firstChar) || firstChar == '0')
		{
			return false;
		}

		return true;
	}

private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e) {
	System::String^ sensibility = this->SensitivityTB->Text;

	if (IsDigitsOnly(sensibility) && IsFirstDigitNonZero(sensibility))
	{
		int myInt = Int32::Parse(sensibility);
		survSys->SetSensitivity(myInt);
	}
	else MessageBox::Show("The sensibility could not be changed");

	bool status = this->RecordStatusCB->Checked;
	survSys->SetIsRecording(status);

	int status_int;
	if (status)
		status_int = 1;
	else status_int = 0;

	ServerIO::getInstance().send_receive("/ " + survSys->getDeviceType() + " " +
		msclr::interop::marshal_as<std::string>(survSys->getLocation()) + " " +
		to_string(survSys->getSensitivity()) + " " + to_string(status_int));

	this->Close();
}
};
}
