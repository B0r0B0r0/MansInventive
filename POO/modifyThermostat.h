#pragma once
#include "Thermostats.h"
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
	/// Summary for modifyThermostat
	/// </summary>
	public ref class modifyThermostat : public System::Windows::Forms::Form
	{
	public:
		Thermostats^ therm;
		modifyThermostat(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

		modifyThermostat(Thermostats^% tm)
		{
			InitializeComponent();
			therm = tm;
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~modifyThermostat()
		{
			if (components)
			{
				delete components;
			}
		}
	private: Bunifu::Framework::UI::BunifuThinButton2^ SaveButton;
	private: System::Windows::Forms::Label^ HumidityLabel;
	protected:

	private: System::Windows::Forms::Label^ labelTemperature;
	private: System::Windows::Forms::TextBox^ HumidityTB;


	private: System::Windows::Forms::TextBox^ TemperatureTB;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(modifyThermostat::typeid));
			this->SaveButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->HumidityLabel = (gcnew System::Windows::Forms::Label());
			this->labelTemperature = (gcnew System::Windows::Forms::Label());
			this->HumidityTB = (gcnew System::Windows::Forms::TextBox());
			this->TemperatureTB = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
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
			this->SaveButton->Click += gcnew System::EventHandler(this, &modifyThermostat::SaveButton_Click);
			// 
			// HumidityLabel
			// 
			this->HumidityLabel->AutoSize = true;
			this->HumidityLabel->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HumidityLabel->Location = System::Drawing::Point(89, 116);
			this->HumidityLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->HumidityLabel->Name = L"HumidityLabel";
			this->HumidityLabel->Size = System::Drawing::Size(93, 28);
			this->HumidityLabel->TabIndex = 40;
			this->HumidityLabel->Text = L"Humidity";
			// 
			// labelTemperature
			// 
			this->labelTemperature->AutoSize = true;
			this->labelTemperature->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelTemperature->Location = System::Drawing::Point(67, 26);
			this->labelTemperature->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTemperature->Name = L"labelTemperature";
			this->labelTemperature->Size = System::Drawing::Size(121, 28);
			this->labelTemperature->TabIndex = 39;
			this->labelTemperature->Text = L"Temperature";
			// 
			// HumidityTB
			// 
			this->HumidityTB->BackColor = System::Drawing::Color::Gainsboro;
			this->HumidityTB->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HumidityTB->Location = System::Drawing::Point(40, 148);
			this->HumidityTB->Margin = System::Windows::Forms::Padding(4);
			this->HumidityTB->Name = L"HumidityTB";
			this->HumidityTB->Size = System::Drawing::Size(190, 39);
			this->HumidityTB->TabIndex = 38;
			// 
			// TemperatureTB
			// 
			this->TemperatureTB->BackColor = System::Drawing::Color::Gainsboro;
			this->TemperatureTB->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TemperatureTB->Location = System::Drawing::Point(40, 58);
			this->TemperatureTB->Margin = System::Windows::Forms::Padding(4);
			this->TemperatureTB->Name = L"TemperatureTB";
			this->TemperatureTB->Size = System::Drawing::Size(190, 39);
			this->TemperatureTB->TabIndex = 37;
			// 
			// modifyThermostat
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(271, 299);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->HumidityLabel);
			this->Controls->Add(this->labelTemperature);
			this->Controls->Add(this->HumidityTB);
			this->Controls->Add(this->TemperatureTB);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"modifyThermostat";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"modifyThermostat";
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
		System::String^ temperature = this->TemperatureTB->Text;
		System::String^ humidity = this->HumidityTB->Text;

		if (IsDigitsOnly(temperature) && IsFirstDigitNonZero(temperature))
		{
			int myInt = Int32::Parse(temperature);
			therm->Settemperature(myInt);
		}
		else MessageBox::Show("The temperature could not be changed");

		if (IsDigitsOnly(humidity) && IsFirstDigitNonZero(humidity))
		{
			int myInt = Int32::Parse(humidity);
			therm->Sethumidity(myInt);
		}
		else MessageBox::Show("The humidity could not be changed");

		ServerIO::getInstance().send_receive("/ " + therm->getDeviceType() + " " +
			msclr::interop::marshal_as<std::string>(therm->getLocation()) + " " +
			to_string(therm->getHumidity()) + " " + to_string(therm->getTemperature()));

		this->Close();
	}
};
}
