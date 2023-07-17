#pragma once
#include "FactoryDevice.h"
#include <Windows.h>
#include <vector>
#include <list>
#include "User.h"
#include "account.h"
#include "modifyBulb.h"
#include "modifySurvSis.h"
#include "modifyThermostat.h"
#include "Info.h"
#include "Loger.h"
#include <sstream>

namespace POO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;


	/// <summary>
	/// Summary for HomePage
	/// </summary>
	public ref class HomePage : public System::Windows::Forms::Form
	{
	public:
		Form^ obj;
		HomePage(void)
		{
			InitializeComponent();
			if (devices == nullptr)
				devices = gcnew List<Device^>();

			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

			if (User::getInstance().isUserAdmin() == false)
				this->Controls->Remove(LogsButton);

			int deviceNr;
			vector<string> serverResponse;

			deviceNr = System::Convert::ToInt32(ServerIO::getInstance().send_receive("6 user1"));


		}

		void addSmallPanel()
		{
			Panel^ subPanel = gcnew Panel();
			subPanel->Size = System::Drawing::Size(PanouDispozitive->Width, 50);
			subPanel->BackColor = Color::Silver;
			subPanel->BorderStyle = BorderStyle::None;
			subPanel->Location = Point(0, (devices->Count - 1) * 50);

			// Creează label-urile și butoanele panoului mic
			Label^ userIdLabel = gcnew Label();
			userIdLabel->Text = "UserId: " + (devices[devices->Count - 1]->getUserId());
			userIdLabel->Location = Point(5, 15);

			Label^ nameLabel = gcnew Label();
			nameLabel->Text = "Name: "
				+ msclr::interop::marshal_as<String^>(devices[devices->Count - 1]->getDeviceType());
			nameLabel->Location = Point(105, 15);

			Label^ locationLabel = gcnew Label();
			if (devices[devices->Count - 1]->getLocation()->Length < 8)
				locationLabel->Text = "Location: " + devices[devices->Count - 1]->getLocation();
			else
				locationLabel->Text = "Location: " + devices[devices->Count - 1]->getLocation()->Substring(0, 7);

			locationLabel->Location = Point(205, 15);

			Button^ onOffButton = gcnew Button();
			if(devices[devices->Count - 1]->getStatus())
				onOffButton->Text = "On";
			else onOffButton->Text = "Off";
			onOffButton->Location = Point(305, 10);

			Button^ modifyButton = gcnew Button();
			modifyButton->Text = "Modify";
			modifyButton->Location = Point(378, 10);

			Button^ deleteButton = gcnew Button();
			deleteButton->Text = "Delete";
			deleteButton->Location = Point(451, 10);

			Button^ infoButton = gcnew Button();
			infoButton->Text = "Info";
			infoButton->Location = Point(524, 10);

			onOffButton->Click += gcnew EventHandler(this, &HomePage::onOffButton_Click);
			modifyButton->Click += gcnew EventHandler(this, &HomePage::modifyButton_Click);
			deleteButton->Click += gcnew EventHandler(this, &HomePage::deleteButton_Click);
			infoButton->Click += gcnew EventHandler(this, &HomePage::infoButton_Click);

			subPanel->Controls->Add(userIdLabel);
			subPanel->Controls->Add(nameLabel);
			subPanel->Controls->Add(locationLabel);
			subPanel->Controls->Add(onOffButton);
			subPanel->Controls->Add(modifyButton);
			subPanel->Controls->Add(deleteButton);
			subPanel->Controls->Add(infoButton);

			// Adaugă panoul mic la panoul mare
			PanouDispozitive->AutoScrollPosition = Point(0, 0);
			PanouDispozitive->Controls->Add(subPanel);
		}

		HomePage(Form^ mf)
		{
			obj = mf;
			InitializeComponent();
			if (devices == nullptr)
				devices = gcnew List<Device^>();

			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

			if (User::getInstance().isUserAdmin() == false)
				this->Controls->Remove(LogsButton);

			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &HomePage::MyForm_FormClosing);

			int deviceNr;
			vector<string> serverResponse;

			deviceNr = System::Convert::ToInt32(ServerIO::getInstance().send_receive("6 " + User::getInstance().getUsername()));

			for (int i = 0; i < deviceNr; i++)
			{
				char buffer[1024];
				size_t received;
				ServerIO::getInstance().getSocket().send("1", 1 + 1);
				ServerIO::getInstance().getSocket().receive(buffer, sizeof(buffer), received);
				
				System::String^ managedString = gcnew System::String(buffer);
				serverResponse.push_back(msclr::interop::marshal_as<std::string>(managedString));
			}

			for (int i = 0; i < deviceNr; i++)
			{
				std::stringstream ss(serverResponse[i]);
				int idUser;
				string username;
				string denumire;
				string locatie;
				int parametrul1;
				int parametrul2;
				bool status;
				
				ss >> idUser;
				ss >> username;
				ss >> denumire;
				ss >> locatie;
				ss >> parametrul1;
				ss >> parametrul2;
				ss >> status;

				String^ location = msclr::interop::marshal_as<String^>(locatie);

				if (denumire == "Bec")
					devices->Add(gcnew Bulbs(parametrul1, parametrul2, idUser, status, location));

				if (denumire == "Termostat")
					devices->Add(gcnew Thermostats(parametrul1, parametrul2, idUser, status, location));

				if (denumire == "Camera")
					devices->Add(gcnew SurveillanceSystem(parametrul1, parametrul2, idUser, status, location));

				addSmallPanel();
			}

		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HomePage()
		{
			if (components)
			{
				delete components;
			}



			if (devices)
				delete devices;
		}
	private: System::Windows::Forms::Panel^ PanouDispozitive;
	private: Bunifu::Framework::UI::BunifuImageButton^ DeviceADD;
	protected:



	private:
	System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
	{
		obj->Show();
	}
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::ComboBox^ cbTipDisp;
	private: System::Windows::Forms::Label^ labelTipDispozitiv;
	private: System::Windows::Forms::Label^ labelLocatie;
	private: System::Windows::Forms::TextBox^ TextBoxLocatie;
	private: Bunifu::Framework::UI::BunifuThinButton2^ LogOutButton;
	private: Bunifu::Framework::UI::BunifuThinButton2^ AccountButton;
	private: Bunifu::Framework::UI::BunifuThinButton2^ LogsButton;
		   System::Collections::Generic::List<Device^>^ devices; // o listă de dispozitive

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(HomePage::typeid));
			this->PanouDispozitive = (gcnew System::Windows::Forms::Panel());
			this->DeviceADD = (gcnew Bunifu::Framework::UI::BunifuImageButton());
			this->cbTipDisp = (gcnew System::Windows::Forms::ComboBox());
			this->labelTipDispozitiv = (gcnew System::Windows::Forms::Label());
			this->labelLocatie = (gcnew System::Windows::Forms::Label());
			this->TextBoxLocatie = (gcnew System::Windows::Forms::TextBox());
			this->LogOutButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->AccountButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->LogsButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DeviceADD))->BeginInit();
			this->SuspendLayout();
			// 
			// PanouDispozitive
			// 
			this->PanouDispozitive->AutoScroll = true;
			this->PanouDispozitive->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->PanouDispozitive->BackColor = System::Drawing::Color::Silver;
			this->PanouDispozitive->Location = System::Drawing::Point(13, 12);
			this->PanouDispozitive->Name = L"PanouDispozitive";
			this->PanouDispozitive->Size = System::Drawing::Size(816, 540);
			this->PanouDispozitive->TabIndex = 0;
			// 
			// DeviceADD
			// 
			this->DeviceADD->BackColor = System::Drawing::Color::Teal;
			this->DeviceADD->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DeviceADD.Image")));
			this->DeviceADD->ImageActive = nullptr;
			this->DeviceADD->Location = System::Drawing::Point(836, 184);
			this->DeviceADD->Name = L"DeviceADD";
			this->DeviceADD->Size = System::Drawing::Size(190, 39);
			this->DeviceADD->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->DeviceADD->TabIndex = 1;
			this->DeviceADD->TabStop = false;
			this->DeviceADD->Zoom = 10;
			this->DeviceADD->Click += gcnew System::EventHandler(this, &HomePage::DeviceADD_Click);
			// 
			// cbTipDisp
			// 
			this->cbTipDisp->BackColor = System::Drawing::Color::Gainsboro;
			this->cbTipDisp->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbTipDisp->DropDownWidth = 150;
			this->cbTipDisp->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbTipDisp->FormattingEnabled = true;
			this->cbTipDisp->IntegralHeight = false;
			this->cbTipDisp->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Bec", L"Termostat", L"Camera" });
			this->cbTipDisp->Location = System::Drawing::Point(836, 35);
			this->cbTipDisp->Margin = System::Windows::Forms::Padding(4);
			this->cbTipDisp->Name = L"cbTipDisp";
			this->cbTipDisp->Size = System::Drawing::Size(190, 40);
			this->cbTipDisp->TabIndex = 26;
			// 
			// labelTipDispozitiv
			// 
			this->labelTipDispozitiv->AutoSize = true;
			this->labelTipDispozitiv->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelTipDispozitiv->Location = System::Drawing::Point(831, 3);
			this->labelTipDispozitiv->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTipDispozitiv->Name = L"labelTipDispozitiv";
			this->labelTipDispozitiv->Size = System::Drawing::Size(115, 28);
			this->labelTipDispozitiv->TabIndex = 29;
			this->labelTipDispozitiv->Text = L"Device Type";
			// 
			// labelLocatie
			// 
			this->labelLocatie->AutoSize = true;
			this->labelLocatie->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelLocatie->Location = System::Drawing::Point(831, 79);
			this->labelLocatie->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelLocatie->Name = L"labelLocatie";
			this->labelLocatie->Size = System::Drawing::Size(87, 28);
			this->labelLocatie->TabIndex = 30;
			this->labelLocatie->Text = L"Location";
			// 
			// TextBoxLocatie
			// 
			this->TextBoxLocatie->BackColor = System::Drawing::Color::Gainsboro;
			this->TextBoxLocatie->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBoxLocatie->Location = System::Drawing::Point(836, 111);
			this->TextBoxLocatie->Margin = System::Windows::Forms::Padding(4);
			this->TextBoxLocatie->Name = L"TextBoxLocatie";
			this->TextBoxLocatie->Size = System::Drawing::Size(190, 39);
			this->TextBoxLocatie->TabIndex = 31;
			// 
			// LogOutButton
			// 
			this->LogOutButton->ActiveBorderThickness = 1;
			this->LogOutButton->ActiveCornerRadius = 20;
			this->LogOutButton->ActiveFillColor = System::Drawing::Color::Teal;
			this->LogOutButton->ActiveForecolor = System::Drawing::Color::White;
			this->LogOutButton->ActiveLineColor = System::Drawing::Color::Teal;
			this->LogOutButton->BackColor = System::Drawing::SystemColors::Control;
			this->LogOutButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"LogOutButton.BackgroundImage")));
			this->LogOutButton->ButtonText = L"LogOut";
			this->LogOutButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->LogOutButton->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LogOutButton->ForeColor = System::Drawing::Color::Teal;
			this->LogOutButton->IdleBorderThickness = 1;
			this->LogOutButton->IdleCornerRadius = 20;
			this->LogOutButton->IdleFillColor = System::Drawing::Color::White;
			this->LogOutButton->IdleForecolor = System::Drawing::Color::Teal;
			this->LogOutButton->IdleLineColor = System::Drawing::Color::Teal;
			this->LogOutButton->Location = System::Drawing::Point(950, 507);
			this->LogOutButton->Margin = System::Windows::Forms::Padding(5);
			this->LogOutButton->Name = L"LogOutButton";
			this->LogOutButton->Size = System::Drawing::Size(96, 55);
			this->LogOutButton->TabIndex = 34;
			this->LogOutButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LogOutButton->Click += gcnew System::EventHandler(this, &HomePage::LogOutButton_Click);
			// 
			// AccountButton
			// 
			this->AccountButton->ActiveBorderThickness = 1;
			this->AccountButton->ActiveCornerRadius = 20;
			this->AccountButton->ActiveFillColor = System::Drawing::Color::Teal;
			this->AccountButton->ActiveForecolor = System::Drawing::Color::White;
			this->AccountButton->ActiveLineColor = System::Drawing::Color::Teal;
			this->AccountButton->BackColor = System::Drawing::SystemColors::Control;
			this->AccountButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AccountButton.BackgroundImage")));
			this->AccountButton->ButtonText = L"Account";
			this->AccountButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->AccountButton->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AccountButton->ForeColor = System::Drawing::Color::Teal;
			this->AccountButton->IdleBorderThickness = 1;
			this->AccountButton->IdleCornerRadius = 20;
			this->AccountButton->IdleFillColor = System::Drawing::Color::White;
			this->AccountButton->IdleForecolor = System::Drawing::Color::Teal;
			this->AccountButton->IdleLineColor = System::Drawing::Color::Teal;
			this->AccountButton->Location = System::Drawing::Point(831, 507);
			this->AccountButton->Margin = System::Windows::Forms::Padding(5);
			this->AccountButton->Name = L"AccountButton";
			this->AccountButton->Size = System::Drawing::Size(114, 55);
			this->AccountButton->TabIndex = 35;
			this->AccountButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->AccountButton->Click += gcnew System::EventHandler(this, &HomePage::AccountButton_Click);
			// 
			// LogsButton
			// 
			this->LogsButton->ActiveBorderThickness = 1;
			this->LogsButton->ActiveCornerRadius = 20;
			this->LogsButton->ActiveFillColor = System::Drawing::Color::Teal;
			this->LogsButton->ActiveForecolor = System::Drawing::Color::White;
			this->LogsButton->ActiveLineColor = System::Drawing::Color::Teal;
			this->LogsButton->BackColor = System::Drawing::SystemColors::Control;
			this->LogsButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"LogsButton.BackgroundImage")));
			this->LogsButton->ButtonText = L"Logs";
			this->LogsButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->LogsButton->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LogsButton->ForeColor = System::Drawing::Color::Teal;
			this->LogsButton->IdleBorderThickness = 1;
			this->LogsButton->IdleCornerRadius = 20;
			this->LogsButton->IdleFillColor = System::Drawing::Color::White;
			this->LogsButton->IdleForecolor = System::Drawing::Color::Teal;
			this->LogsButton->IdleLineColor = System::Drawing::Color::Teal;
			this->LogsButton->Location = System::Drawing::Point(831, 458);
			this->LogsButton->Margin = System::Windows::Forms::Padding(5);
			this->LogsButton->Name = L"LogsButton";
			this->LogsButton->Size = System::Drawing::Size(215, 55);
			this->LogsButton->TabIndex = 36;
			this->LogsButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LogsButton->Click += gcnew System::EventHandler(this, &HomePage::LogsButton_Click);
			// 
			// HomePage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1051, 564);
			this->Controls->Add(this->LogsButton);
			this->Controls->Add(this->AccountButton);
			this->Controls->Add(this->LogOutButton);
			this->Controls->Add(this->DeviceADD);
			this->Controls->Add(this->TextBoxLocatie);
			this->Controls->Add(this->labelLocatie);
			this->Controls->Add(this->labelTipDispozitiv);
			this->Controls->Add(this->cbTipDisp);
			this->Controls->Add(this->PanouDispozitive);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"HomePage";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HomePage";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DeviceADD))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void DeviceADD_Click(System::Object^ sender, System::EventArgs^ e) {
	
		if (HomePage::cbTipDisp->Text->Length == 0)
		{
			MessageBox::Show("You haven't specified the type of device.");
			return;
		}

		if(HomePage::TextBoxLocatie->Text->Length == 0)
		{
			MessageBox::Show("You haven't provided the location of the device.");
			return;
		}

		if(devices->Count >= 10)
		{
			MessageBox::Show("Maximum capacity of devices reached. To add more devices, purchase the premium plan by contacting us at smartHome@premiumplan.ro");
			return;
		}

		String^ response;

		if (HomePage::cbTipDisp->Text == "Bec")
		{
			devices->Add(deviceFactory::getDeviceFromFactory(devieType::BULB, 0, HomePage::TextBoxLocatie->Text));
			response = ServerIO::getInstance().send_receive("5 " + User::getInstance().getUsername() + " Bec "
				+ msclr::interop::marshal_as<std::string>(devices[devices->Count - 1]->getLocation()) + " 10 10");
		}

		if (HomePage::cbTipDisp->Text == "Termostat")
		{
			devices->Add(deviceFactory::getDeviceFromFactory(devieType::THERMOSTAT, 0, HomePage::TextBoxLocatie->Text));
			response = ServerIO::getInstance().send_receive("5 " + User::getInstance().getUsername() + " Termostat "
				+ msclr::interop::marshal_as<std::string>(devices[devices->Count - 1]->getLocation()) + " 22 10");
		}

		if (HomePage::cbTipDisp->Text == "Camera")
		{
			devices->Add(deviceFactory::getDeviceFromFactory(devieType::SURVEILLANCESYSTEM, 0, HomePage::TextBoxLocatie->Text));
			response = ServerIO::getInstance().send_receive("5 " + User::getInstance().getUsername() + " Camera "
				+ msclr::interop::marshal_as<std::string>(devices[devices->Count - 1]->getLocation()) + " 1 10");
		}

		if (response == "Exista deja in BD")
		{
			devices->RemoveAt(devices->Count - 1);
			MessageBox::Show("Device already in DB!");
			return;
		}

		addSmallPanel();
	}

	private: System::Void onOffButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ clickedButton = dynamic_cast<Button^>(sender);
		if (clickedButton != nullptr)
		{
			// caută panoul părinte al butonului apăsat (adica panoul mic al dispozitivului)
			Panel^ subPanel = dynamic_cast<Panel^>(clickedButton->Parent);
			if (subPanel != nullptr)
			{
				// caută indexul dispozitivului în lista de dispozitive
				int deviceIndex = (subPanel->Location.Y + this->PanouDispozitive->VerticalScroll->Value) / 50;
				
				// obține dispozitivul din lista de dispozitive
				Device^ device = devices[deviceIndex];
				// comută starea dispozitivului
				device->ToggleOnOff();

				// actualizează textul butonului în funcție de starea dispozitivului
				if (device->getStatus() == true)
				{
					clickedButton->Text = "On";
					ServerIO::getInstance().send_receive("8 " + device->getDeviceType()
						+ " " + msclr::interop::marshal_as<std::string>(device->getLocation()));

					return;
				}
				else clickedButton->Text = "Off";
				{
					ServerIO::getInstance().send_receive("7 " + device->getDeviceType()
						+ " " + msclr::interop::marshal_as<std::string>(device->getLocation()));

					return;
				}
			}
		}

	}

	private: System::Void modifyButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ clickedButton = dynamic_cast<Button^>(sender);
		if (clickedButton != nullptr)
		{
			// caută panoul părinte al butonului apăsat (adica panoul mic al dispozitivului)
			Panel^ subPanel = dynamic_cast<Panel^>(clickedButton->Parent);
			if (subPanel != nullptr)
			{
				// caută indexul dispozitivului în lista de dispozitive
				int deviceIndex = (subPanel->Location.Y + this->PanouDispozitive->VerticalScroll->Value) / 50;

				// obține dispozitivul din lista de dispozitive
				Device^ device = devices[deviceIndex];

				if (device->getStatus() == false)
					return;

				if (device->getDeviceType() == "Bec")
				{
					Bulbs^ bulb = dynamic_cast<Bulbs^>(device);
					modifyBulb^ obj = gcnew modifyBulb(bulb);
					obj->ShowDialog();
				}

				if (device->getDeviceType() == "Termostat")
				{
					Thermostats^ ther = dynamic_cast<Thermostats^>(device);
					modifyThermostat^ obj = gcnew modifyThermostat(ther);
					obj->ShowDialog();
				}

				if (device->getDeviceType() == "Camera")
				{
					SurveillanceSystem^ ss = dynamic_cast<SurveillanceSystem^>(device);
					modifySurvSis^ obj = gcnew modifySurvSis(ss);
					obj->ShowDialog();
				}
			}
		}
	}

	private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ clickedButton = dynamic_cast<Button^>(sender);
		if (clickedButton != nullptr)
		{
			// caută panoul părinte al butonului apăsat (adica panoul mic al dispozitivului)
			Panel^ subPanel = dynamic_cast<Panel^>(clickedButton->Parent);
			if (subPanel != nullptr)
			{
				// caută indexul dispozitivului în lista de dispozitive
				int deviceIndex = (subPanel->Location.Y + this->PanouDispozitive->VerticalScroll->Value) / 50;

				ServerIO::getInstance().send_receive("9 " + devices[deviceIndex]->getDeviceType()
					+ " " + msclr::interop::marshal_as<std::string>(devices[deviceIndex]->getLocation()));

				devices->RemoveAt(deviceIndex);
				PanouDispozitive->Controls->RemoveAt(deviceIndex);

				if(deviceIndex<devices->Count)
				{
					for (int i = deviceIndex; i < devices->Count; i++)
						PanouDispozitive->Controls[i]->Location
						= Point(0, PanouDispozitive->Controls[i]->Location.Y - 50);

					for (int i = 0; i < devices->Count; i++)
						PanouDispozitive->Controls[i]->Refresh();
				}

				PanouDispozitive->AutoScrollPosition = Point(0, 0);
			}
		}
	}

	private: System::Void infoButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ clickedButton = dynamic_cast<Button^>(sender);
		if (clickedButton != nullptr)
		{
			// caută panoul părinte al butonului apăsat (adica panoul mic al dispozitivului)
			Panel^ subPanel = dynamic_cast<Panel^>(clickedButton->Parent);
			if (subPanel != nullptr)
			{
				// caută indexul dispozitivului în lista de dispozitive
				int deviceIndex = (subPanel->Location.Y + this->PanouDispozitive->VerticalScroll->Value) / 50;

				// obține dispozitivul din lista de dispozitive
				Device^ device = devices[deviceIndex];
				
				Info^ obj = gcnew Info(device);
				obj->ShowDialog();
			}
		}
	}

private: System::Void LogOutButton_Click(System::Object^ sender, System::EventArgs^ e) {
	HomePage::devices->Clear();
	User::getInstance().destroyInstance();
	ServerIO::getInstance().send_receive("disclient");
	this->Close();
	obj->Show();
}
private: System::Void AccountButton_Click(System::Object^ sender, System::EventArgs^ e) {
	account^ obj = gcnew account(this);
	obj->ShowDialog();;
}

private: System::Void LogsButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Loger::getInstance().showLog();
}
};
}