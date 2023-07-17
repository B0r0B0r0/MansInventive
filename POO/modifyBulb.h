#pragma once
#include "Bulbs.h"
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
	/// Summary for modifyBulb
	/// </summary>
	public ref class modifyBulb : public System::Windows::Forms::Form
	{
	public:
		Bulbs^ bulb;
		modifyBulb(void)
		{
			InitializeComponent();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

		modifyBulb(Bulbs^% BULB)
		{
			InitializeComponent();
			bulb = BULB;
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~modifyBulb()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ BrightnessTB;
	private: System::Windows::Forms::TextBox^ ColorTempTB;
	protected:

	protected:

	private: System::Windows::Forms::Label^ labelBrightness;
	private: System::Windows::Forms::Label^ label1;
	private: Bunifu::Framework::UI::BunifuThinButton2^ SaveButton;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(modifyBulb::typeid));
			this->BrightnessTB = (gcnew System::Windows::Forms::TextBox());
			this->ColorTempTB = (gcnew System::Windows::Forms::TextBox());
			this->labelBrightness = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SaveButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->SuspendLayout();
			// 
			// BrightnessTB
			// 
			this->BrightnessTB->BackColor = System::Drawing::Color::Gainsboro;
			this->BrightnessTB->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BrightnessTB->Location = System::Drawing::Point(39, 61);
			this->BrightnessTB->Margin = System::Windows::Forms::Padding(4);
			this->BrightnessTB->Name = L"BrightnessTB";
			this->BrightnessTB->Size = System::Drawing::Size(190, 39);
			this->BrightnessTB->TabIndex = 32;
			// 
			// ColorTempTB
			// 
			this->ColorTempTB->BackColor = System::Drawing::Color::Gainsboro;
			this->ColorTempTB->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ColorTempTB->Location = System::Drawing::Point(39, 151);
			this->ColorTempTB->Margin = System::Windows::Forms::Padding(4);
			this->ColorTempTB->Name = L"ColorTempTB";
			this->ColorTempTB->Size = System::Drawing::Size(190, 39);
			this->ColorTempTB->TabIndex = 33;
			// 
			// labelBrightness
			// 
			this->labelBrightness->AutoSize = true;
			this->labelBrightness->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelBrightness->Location = System::Drawing::Point(83, 29);
			this->labelBrightness->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelBrightness->Name = L"labelBrightness";
			this->labelBrightness->Size = System::Drawing::Size(102, 28);
			this->labelBrightness->TabIndex = 34;
			this->labelBrightness->Text = L"Brightness";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(47, 119);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(173, 28);
			this->label1->TabIndex = 35;
			this->label1->Text = L"Color temperature";
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
			this->SaveButton->Location = System::Drawing::Point(71, 220);
			this->SaveButton->Margin = System::Windows::Forms::Padding(5);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(129, 55);
			this->SaveButton->TabIndex = 36;
			this->SaveButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->SaveButton->Click += gcnew System::EventHandler(this, &modifyBulb::SaveButton_Click);
			// 
			// modifyBulb
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(271, 299);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->labelBrightness);
			this->Controls->Add(this->ColorTempTB);
			this->Controls->Add(this->BrightnessTB);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"modifyBulb";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"modifyBulb";
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
	System::String^ brightness = this->BrightnessTB->Text;
	System::String^ colorTemperature = this->ColorTempTB->Text;

	if (IsDigitsOnly(brightness) && IsFirstDigitNonZero(brightness))
	{
		int myInt = Int32::Parse(brightness);
		bulb->SetBrightness(myInt);
	}
	else MessageBox::Show("The brightness could not be changed");

	if (IsDigitsOnly(colorTemperature) && IsFirstDigitNonZero(colorTemperature))
	{
		int myInt = Int32::Parse(colorTemperature);
		bulb->SetColorTemperature(myInt);
	}
	else MessageBox::Show("The color temperature could not be changed");

	ServerIO::getInstance().send_receive("/ " + bulb->getDeviceType() + " " +
		msclr::interop::marshal_as<std::string>(bulb->getLocation()) + " " + 
		to_string(bulb->getBrightness()) + " " + to_string(bulb->getColorTemperature()));

	this->Close();
}
};
}
