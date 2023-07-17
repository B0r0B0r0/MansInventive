#pragma once
#include "HomePage.h"
#include "ServerIO.h"
#include <sstream>

namespace POO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			ServerIO::getInstance().send_receive("client");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ welcome_label;
	protected:
	private: System::Windows::Forms::Panel^ panouRegister;
	private: Bunifu::Framework::UI::BunifuTextbox^ Register_adminCode;
	private: Bunifu::Framework::UI::BunifuTextbox^ Register_Email;
	private: Bunifu::Framework::UI::BunifuTextbox^ Register_password;
	private: Bunifu::Framework::UI::BunifuTextbox^ Register_usename;
	private: System::Windows::Forms::Label^ RegisterLabel;
	private: System::Windows::Forms::Panel^ panouLogin;
	private: Bunifu::Framework::UI::BunifuTextbox^ Login_password;
	private: Bunifu::Framework::UI::BunifuTextbox^ Login_username;
	private: System::Windows::Forms::Label^ Login_label;
	private: Bunifu::Framework::UI::BunifuTextbox^ Register_ConfirmPassword;
	private: Bunifu::Framework::UI::BunifuThinButton2^ Register_button;
	private: Bunifu::Framework::UI::BunifuThinButton2^ Login_Button;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->welcome_label = (gcnew System::Windows::Forms::Label());
			this->panouRegister = (gcnew System::Windows::Forms::Panel());
			this->Register_button = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->Register_ConfirmPassword = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->Register_adminCode = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->Register_Email = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->Register_password = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->Register_usename = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->RegisterLabel = (gcnew System::Windows::Forms::Label());
			this->panouLogin = (gcnew System::Windows::Forms::Panel());
			this->Login_Button = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->Login_password = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->Login_username = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->Login_label = (gcnew System::Windows::Forms::Label());
			this->panouRegister->SuspendLayout();
			this->panouLogin->SuspendLayout();
			this->SuspendLayout();
			// 
			// welcome_label
			// 
			this->welcome_label->AutoSize = true;
			this->welcome_label->BackColor = System::Drawing::Color::White;
			this->welcome_label->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 19.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->welcome_label->Location = System::Drawing::Point(467, 189);
			this->welcome_label->Name = L"welcome_label";
			this->welcome_label->Size = System::Drawing::Size(143, 42);
			this->welcome_label->TabIndex = 7;
			this->welcome_label->Text = L"Welcome";
			this->welcome_label->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// panouRegister
			// 
			this->panouRegister->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panouRegister->Controls->Add(this->Register_button);
			this->panouRegister->Controls->Add(this->Register_ConfirmPassword);
			this->panouRegister->Controls->Add(this->Register_adminCode);
			this->panouRegister->Controls->Add(this->Register_Email);
			this->panouRegister->Controls->Add(this->Register_password);
			this->panouRegister->Controls->Add(this->Register_usename);
			this->panouRegister->Controls->Add(this->RegisterLabel);
			this->panouRegister->Location = System::Drawing::Point(647, 12);
			this->panouRegister->Name = L"panouRegister";
			this->panouRegister->Size = System::Drawing::Size(423, 479);
			this->panouRegister->TabIndex = 6;
			// 
			// Register_button
			// 
			this->Register_button->ActiveBorderThickness = 1;
			this->Register_button->ActiveCornerRadius = 20;
			this->Register_button->ActiveFillColor = System::Drawing::Color::Black;
			this->Register_button->ActiveForecolor = System::Drawing::Color::White;
			this->Register_button->ActiveLineColor = System::Drawing::Color::Black;
			this->Register_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->Register_button->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_button.BackgroundImage")));
			this->Register_button->ButtonText = L"Register";
			this->Register_button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Register_button->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Register_button->ForeColor = System::Drawing::Color::Black;
			this->Register_button->IdleBorderThickness = 1;
			this->Register_button->IdleCornerRadius = 20;
			this->Register_button->IdleFillColor = System::Drawing::Color::White;
			this->Register_button->IdleForecolor = System::Drawing::Color::Black;
			this->Register_button->IdleLineColor = System::Drawing::Color::Black;
			this->Register_button->Location = System::Drawing::Point(129, 409);
			this->Register_button->Margin = System::Windows::Forms::Padding(5);
			this->Register_button->Name = L"Register_button";
			this->Register_button->Size = System::Drawing::Size(181, 41);
			this->Register_button->TabIndex = 5;
			this->Register_button->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Register_button->Click += gcnew System::EventHandler(this, &MyForm::Register_button_Click);
			// 
			// Register_ConfirmPassword
			// 
			this->Register_ConfirmPassword->BackColor = System::Drawing::Color::Silver;
			this->Register_ConfirmPassword->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_ConfirmPassword.BackgroundImage")));
			this->Register_ConfirmPassword->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Register_ConfirmPassword->ForeColor = System::Drawing::Color::Black;
			this->Register_ConfirmPassword->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_ConfirmPassword.Icon")));
			this->Register_ConfirmPassword->Location = System::Drawing::Point(77, 196);
			this->Register_ConfirmPassword->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Register_ConfirmPassword->Name = L"Register_ConfirmPassword";
			this->Register_ConfirmPassword->Size = System::Drawing::Size(281, 54);
			this->Register_ConfirmPassword->TabIndex = 5;
			this->Register_ConfirmPassword->text = L"Confirm password";
			this->Register_ConfirmPassword->OnTextChange += gcnew System::EventHandler(this, &MyForm::Register_ConfirmPassword_OnTextChange);
			this->Register_ConfirmPassword->Click += gcnew System::EventHandler(this, &MyForm::Register_ConfirmPassword_Click);
			// 
			// Register_adminCode
			// 
			this->Register_adminCode->BackColor = System::Drawing::Color::Silver;
			this->Register_adminCode->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_adminCode.BackgroundImage")));
			this->Register_adminCode->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Register_adminCode->ForeColor = System::Drawing::Color::Black;
			this->Register_adminCode->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_adminCode.Icon")));
			this->Register_adminCode->Location = System::Drawing::Point(77, 320);
			this->Register_adminCode->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Register_adminCode->Name = L"Register_adminCode";
			this->Register_adminCode->Size = System::Drawing::Size(281, 54);
			this->Register_adminCode->TabIndex = 4;
			this->Register_adminCode->text = L"Admin code";
			this->Register_adminCode->Click += gcnew System::EventHandler(this, &MyForm::Register_adminCode_Click);
			// 
			// Register_Email
			// 
			this->Register_Email->BackColor = System::Drawing::Color::Silver;
			this->Register_Email->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_Email.BackgroundImage")));
			this->Register_Email->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Register_Email->ForeColor = System::Drawing::Color::Black;
			this->Register_Email->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_Email.Icon")));
			this->Register_Email->Location = System::Drawing::Point(77, 258);
			this->Register_Email->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Register_Email->Name = L"Register_Email";
			this->Register_Email->Size = System::Drawing::Size(281, 54);
			this->Register_Email->TabIndex = 3;
			this->Register_Email->text = L"Email";
			this->Register_Email->Click += gcnew System::EventHandler(this, &MyForm::Register_Email_Click);
			// 
			// Register_password
			// 
			this->Register_password->BackColor = System::Drawing::Color::Silver;
			this->Register_password->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_password.BackgroundImage")));
			this->Register_password->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Register_password->ForeColor = System::Drawing::Color::Black;
			this->Register_password->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_password.Icon")));
			this->Register_password->Location = System::Drawing::Point(77, 134);
			this->Register_password->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Register_password->Name = L"Register_password";
			this->Register_password->Size = System::Drawing::Size(281, 54);
			this->Register_password->TabIndex = 2;
			this->Register_password->text = L"Password";
			this->Register_password->OnTextChange += gcnew System::EventHandler(this, &MyForm::Register_password_OnTextChange);
			this->Register_password->Click += gcnew System::EventHandler(this, &MyForm::Register_password_Click);
			// 
			// Register_usename
			// 
			this->Register_usename->BackColor = System::Drawing::Color::Silver;
			this->Register_usename->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_usename.BackgroundImage")));
			this->Register_usename->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Register_usename->ForeColor = System::Drawing::Color::Black;
			this->Register_usename->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Register_usename.Icon")));
			this->Register_usename->Location = System::Drawing::Point(77, 72);
			this->Register_usename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Register_usename->Name = L"Register_usename";
			this->Register_usename->Size = System::Drawing::Size(281, 54);
			this->Register_usename->TabIndex = 1;
			this->Register_usename->text = L"Username";
			this->Register_usename->Click += gcnew System::EventHandler(this, &MyForm::Register_usename_Click);
			// 
			// RegisterLabel
			// 
			this->RegisterLabel->AutoSize = true;
			this->RegisterLabel->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 19.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RegisterLabel->Location = System::Drawing::Point(138, 0);
			this->RegisterLabel->Name = L"RegisterLabel";
			this->RegisterLabel->Size = System::Drawing::Size(132, 42);
			this->RegisterLabel->TabIndex = 0;
			this->RegisterLabel->Text = L"Register";
			this->RegisterLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// panouLogin
			// 
			this->panouLogin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->panouLogin->Controls->Add(this->Login_Button);
			this->panouLogin->Controls->Add(this->Login_password);
			this->panouLogin->Controls->Add(this->Login_username);
			this->panouLogin->Controls->Add(this->Login_label);
			this->panouLogin->Location = System::Drawing::Point(12, 12);
			this->panouLogin->Name = L"panouLogin";
			this->panouLogin->Size = System::Drawing::Size(423, 479);
			this->panouLogin->TabIndex = 5;
			// 
			// Login_Button
			// 
			this->Login_Button->ActiveBorderThickness = 1;
			this->Login_Button->ActiveCornerRadius = 20;
			this->Login_Button->ActiveFillColor = System::Drawing::Color::Black;
			this->Login_Button->ActiveForecolor = System::Drawing::Color::White;
			this->Login_Button->ActiveLineColor = System::Drawing::Color::Black;
			this->Login_Button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->Login_Button->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Login_Button.BackgroundImage")));
			this->Login_Button->ButtonText = L"Login";
			this->Login_Button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Login_Button->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Login_Button->ForeColor = System::Drawing::Color::Black;
			this->Login_Button->IdleBorderThickness = 1;
			this->Login_Button->IdleCornerRadius = 20;
			this->Login_Button->IdleFillColor = System::Drawing::Color::White;
			this->Login_Button->IdleForecolor = System::Drawing::Color::Black;
			this->Login_Button->IdleLineColor = System::Drawing::Color::Black;
			this->Login_Button->Location = System::Drawing::Point(109, 409);
			this->Login_Button->Margin = System::Windows::Forms::Padding(5);
			this->Login_Button->Name = L"Login_Button";
			this->Login_Button->Size = System::Drawing::Size(181, 41);
			this->Login_Button->TabIndex = 4;
			this->Login_Button->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Login_Button->Click += gcnew System::EventHandler(this, &MyForm::Login_Button_Click);
			// 
			// Login_password
			// 
			this->Login_password->BackColor = System::Drawing::Color::Silver;
			this->Login_password->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Login_password.BackgroundImage")));
			this->Login_password->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Login_password->ForeColor = System::Drawing::Color::Black;
			this->Login_password->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Login_password.Icon")));
			this->Login_password->Location = System::Drawing::Point(63, 134);
			this->Login_password->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Login_password->Name = L"Login_password";
			this->Login_password->Size = System::Drawing::Size(281, 54);
			this->Login_password->TabIndex = 3;
			this->Login_password->text = L"Password";
			this->Login_password->OnTextChange += gcnew System::EventHandler(this, &MyForm::Login_password_OnTextChange);
			this->Login_password->Click += gcnew System::EventHandler(this, &MyForm::Login_password_Click);
			// 
			// Login_username
			// 
			this->Login_username->BackColor = System::Drawing::Color::Silver;
			this->Login_username->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Login_username.BackgroundImage")));
			this->Login_username->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Login_username->ForeColor = System::Drawing::Color::Black;
			this->Login_username->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Login_username.Icon")));
			this->Login_username->Location = System::Drawing::Point(63, 72);
			this->Login_username->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Login_username->Name = L"Login_username";
			this->Login_username->Size = System::Drawing::Size(281, 54);
			this->Login_username->TabIndex = 2;
			this->Login_username->text = L"Username";
			this->Login_username->Click += gcnew System::EventHandler(this, &MyForm::Login_username_Click);
			// 
			// Login_label
			// 
			this->Login_label->AutoSize = true;
			this->Login_label->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 19.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Login_label->Location = System::Drawing::Point(147, 0);
			this->Login_label->Name = L"Login_label";
			this->Login_label->Size = System::Drawing::Size(97, 42);
			this->Login_label->TabIndex = 1;
			this->Login_label->Text = L"Login";
			this->Login_label->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1082, 503);
			this->Controls->Add(this->welcome_label);
			this->Controls->Add(this->panouRegister);
			this->Controls->Add(this->panouLogin);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Smart-Home";
			this->panouRegister->ResumeLayout(false);
			this->panouRegister->PerformLayout();
			this->panouLogin->ResumeLayout(false);
			this->panouLogin->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Login_password_OnTextChange(System::Object^ sender, System::EventArgs^ e) {
		/*String^ text = this->Login_password->text;
		if(text->Length)
		{
			String^ tag = dynamic_cast<String^>(this->Login_password->Tag);
			tag += text[text->Length - 1];
			this->Login_password->Tag = tag;
		}
		String^ textMascat = gcnew String('*', text->Length);
		this->Login_password->text = textMascat;*/
	}
private: System::Void Register_password_OnTextChange(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Register_ConfirmPassword_OnTextChange(System::Object^ sender, System::EventArgs^ e) {
	/*String^ text = this->Register_ConfirmPassword->text;
	String^ textMascat = gcnew String('*', text->Length);
	this->Register_ConfirmPassword->text = textMascat;*/
}
private: System::Void Login_username_Click(System::Object ^ sender, System::EventArgs ^ e) {
	if (Login_username->text == "Username")
		Login_username->text = "";
}
private: System::Void Login_password_Click(System::Object^ sender, System::EventArgs^ e) {
	if (Login_password->text == "Password")
		Login_password->text = "";
}
private: System::Void Register_usename_Click(System::Object^ sender, System::EventArgs^ e) {
	if (Register_usename->text == "Username")
		Register_usename->text = "";
}
private: System::Void Register_password_Click(System::Object^ sender, System::EventArgs^ e) {
	if (Register_password->text == "Password")
		Register_password->text = "";
}
private: System::Void Register_ConfirmPassword_Click(System::Object^ sender, System::EventArgs^ e) {
	if (Register_ConfirmPassword->text == "Confirm password")
		Register_ConfirmPassword->text = "";
}
private: System::Void Register_Email_Click(System::Object^ sender, System::EventArgs^ e) {
	if (Register_Email->text == "Email")
		Register_Email->text = "";
}
private: System::Void Register_adminCode_Click(System::Object^ sender, System::EventArgs^ e) {
	if (Register_adminCode->text == "Admin code")
		Register_adminCode->text = "";
}
private: System::Void Login_Button_Click(System::Object^ sender, System::EventArgs^ e) {
	string username = marshal_as<string>(this->Login_username->text);
	string password = marshal_as<string>(this->Login_password->text);
	string email;
	bool isAdmin;
	int userId;

	System::String^ serverMessage;
	serverMessage = ServerIO::getInstance().send_receive("1 " + username + " " + password);

	if (serverMessage == "Not in BD")
		MessageBox::Show("This user is not registered");
	else
		if(serverMessage == "Wrong Password")
			MessageBox::Show("Wrong password");
		else
		{
			std::stringstream ss(msclr::interop::marshal_as<std::string>(serverMessage));
			ss >> userId;
			ss >> email;
			ss >> isAdmin;
			//verificare in BD
			//obtinere date
			User::getInstance(username, password, email, isAdmin, userId);
			HomePage^ obj = gcnew HomePage(this);
			this->Hide();
			obj->ShowDialog();
		}
}
private: System::Void Register_button_Click(System::Object^ sender, System::EventArgs^ e) {
	string username = marshal_as<string>(this->Register_usename->text);
	string password = marshal_as<string>(this->Register_password->text);
	string confirm_password = marshal_as<string>(this->Register_ConfirmPassword->text);
	string email = marshal_as<string>(this->Register_Email->text);
	string adminCode = marshal_as<string>(this->Register_adminCode->text);
	int userId;
	int statusAdmin;

	if (username == "Username"  ||
		password == "Password"  ||
		confirm_password == "Confirm password" || 
		email == "Email" ||
		password != confirm_password)
	{
		MessageBox::Show("Date de inregistrare invalide!");
		return;
	}

	if (adminCode == "ADMIN")
		statusAdmin = 1;
	else
		statusAdmin = 0;

	//get userId
	ServerIO::getInstance().send_receive("0 " + username + " " + password + " " + email + " " + to_string(statusAdmin));
	MessageBox::Show("Account create successfully! Please log in!");
	/*if (adminCode == "ADMIN")
		User::getInstance(username, password, email, true, userId);
	else
		User::getInstance(username, password, email, false, userId);

	HomePage^ obj = gcnew HomePage(this);
	this->Hide();
	obj->ShowDialog();*/
	}

};
}
