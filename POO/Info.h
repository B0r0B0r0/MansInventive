#pragma once
#include "Bulbs.h"
#include "Thermostats.h"
#include "SurveillanceSystem.h"
#include <msclr/marshal_cppstd.h>

namespace POO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Info
	/// </summary>
	public ref class Info : public System::Windows::Forms::Form
	{
	public:
		Bulbs^ bulb;
		Thermostats^ term;
	private: System::Windows::Forms::Label^ labelDI;
	public:
		SurveillanceSystem^ ss;

		Info(void)
		{
			InitializeComponent();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

		Info(Device^% device)
		{
			InitializeComponent();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

			if (device->getDeviceType() == "Bec")
			{
				bulb = dynamic_cast<Bulbs^>(device);
				this->labelParam1->Text = "Brightness: " + bulb->getBrightness();
				this->labelparameter2->Text = "Color temperature: " + bulb->getColorTemperature();
			}

			if (device->getDeviceType() == "Termostat")
			{
				term = dynamic_cast<Thermostats^>(device);
				this->labelParam1->Text = "Temperature: " + term->getTemperature();
				this->labelparameter2->Text = "Humidity: " + term->getHumidity();
			}

			if (device->getDeviceType() == "Camera")
			{
				ss = dynamic_cast<SurveillanceSystem^>(device);
				this->labelParam1->Text = "Sensitivity: " + ss->getSensitivity();
				this->labelparameter2->Text = "Is recording: " + ss->getIsRecording();
			}

			this->labelUserId->Text = this->labelUserId->Text + " " + device->getUserId();
			this->labelDeviceType->Text = this->labelDeviceType->Text + " " + 
				msclr::interop::marshal_as<System::String^>(device->getDeviceType());
			this->labelLocation->Text = this->labelLocation->Text + " " + device->getLocation();

			if(device->getStatus())
				this->labelStatus->Text = this->labelStatus->Text + " ON";
			else
				this->labelStatus->Text = this->labelStatus->Text + " OFF";

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Info()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labelParam1;
	private: System::Windows::Forms::Label^ labelUserId;
	private: System::Windows::Forms::Label^ labelDeviceType;
	private: System::Windows::Forms::Label^ labelLocation;
	private: System::Windows::Forms::Label^ labelparameter2;
	private: System::Windows::Forms::Label^ labelStatus;


	protected:

	protected:





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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Info::typeid));
			this->labelParam1 = (gcnew System::Windows::Forms::Label());
			this->labelUserId = (gcnew System::Windows::Forms::Label());
			this->labelDeviceType = (gcnew System::Windows::Forms::Label());
			this->labelLocation = (gcnew System::Windows::Forms::Label());
			this->labelparameter2 = (gcnew System::Windows::Forms::Label());
			this->labelStatus = (gcnew System::Windows::Forms::Label());
			this->labelDI = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// labelParam1
			// 
			this->labelParam1->AutoSize = true;
			this->labelParam1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelParam1->Location = System::Drawing::Point(12, 185);
			this->labelParam1->Name = L"labelParam1";
			this->labelParam1->Size = System::Drawing::Size(119, 25);
			this->labelParam1->TabIndex = 0;
			this->labelParam1->Text = L"Parameter1:";
			// 
			// labelUserId
			// 
			this->labelUserId->AutoSize = true;
			this->labelUserId->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelUserId->Location = System::Drawing::Point(12, 63);
			this->labelUserId->Name = L"labelUserId";
			this->labelUserId->Size = System::Drawing::Size(79, 25);
			this->labelUserId->TabIndex = 1;
			this->labelUserId->Text = L"User id:";
			// 
			// labelDeviceType
			// 
			this->labelDeviceType->AutoSize = true;
			this->labelDeviceType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelDeviceType->Location = System::Drawing::Point(12, 104);
			this->labelDeviceType->Name = L"labelDeviceType";
			this->labelDeviceType->Size = System::Drawing::Size(120, 25);
			this->labelDeviceType->TabIndex = 2;
			this->labelDeviceType->Text = L"Device type:";
			// 
			// labelLocation
			// 
			this->labelLocation->AutoSize = true;
			this->labelLocation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelLocation->Location = System::Drawing::Point(12, 144);
			this->labelLocation->Name = L"labelLocation";
			this->labelLocation->Size = System::Drawing::Size(92, 25);
			this->labelLocation->TabIndex = 3;
			this->labelLocation->Text = L"Location:";
			// 
			// labelparameter2
			// 
			this->labelparameter2->AutoSize = true;
			this->labelparameter2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelparameter2->Location = System::Drawing::Point(12, 226);
			this->labelparameter2->Name = L"labelparameter2";
			this->labelparameter2->Size = System::Drawing::Size(119, 25);
			this->labelparameter2->TabIndex = 4;
			this->labelparameter2->Text = L"Parameter2:";
			// 
			// labelStatus
			// 
			this->labelStatus->AutoSize = true;
			this->labelStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelStatus->Location = System::Drawing::Point(12, 268);
			this->labelStatus->Name = L"labelStatus";
			this->labelStatus->Size = System::Drawing::Size(74, 25);
			this->labelStatus->TabIndex = 5;
			this->labelStatus->Text = L"Status:";
			// 
			// labelDI
			// 
			this->labelDI->AutoSize = true;
			this->labelDI->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 19.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelDI->Location = System::Drawing::Point(42, 9);
			this->labelDI->Name = L"labelDI";
			this->labelDI->Size = System::Drawing::Size(176, 42);
			this->labelDI->TabIndex = 6;
			this->labelDI->Text = L"Device Info";
			this->labelDI->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Info
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(271, 299);
			this->Controls->Add(this->labelDI);
			this->Controls->Add(this->labelStatus);
			this->Controls->Add(this->labelparameter2);
			this->Controls->Add(this->labelLocation);
			this->Controls->Add(this->labelDeviceType);
			this->Controls->Add(this->labelUserId);
			this->Controls->Add(this->labelParam1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Info";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Info";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma 
};
}
