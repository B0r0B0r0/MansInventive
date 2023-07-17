#pragma once
#include <msclr/marshal_cppstd.h>
#include "ServerIO.h"
#include "User.h"

namespace POO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for account
	/// </summary>
	public ref class account : public System::Windows::Forms::Form
	{
	public:
		Form^ obj;
		account(void)
		{
			InitializeComponent();
			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

		account(Form^ mf)
		{
			obj = mf;
			InitializeComponent();

			this->MaximizeBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~account()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labelSchimbarePass;
	private: Bunifu::Framework::UI::BunifuTextbox^ OldPassword;
	private: Bunifu::Framework::UI::BunifuTextbox^ newPassword;
	private: System::Windows::Forms::Label^ LabelEmail;
	private: Bunifu::Framework::UI::BunifuTextbox^ newEmail;
	private: Bunifu::Framework::UI::BunifuThinButton2^ SaveButton;
	private: Bunifu::Framework::UI::BunifuThinButton2^ deleteAccountButton;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(account::typeid));
			this->labelSchimbarePass = (gcnew System::Windows::Forms::Label());
			this->OldPassword = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->newPassword = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->LabelEmail = (gcnew System::Windows::Forms::Label());
			this->newEmail = (gcnew Bunifu::Framework::UI::BunifuTextbox());
			this->SaveButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->deleteAccountButton = (gcnew Bunifu::Framework::UI::BunifuThinButton2());
			this->SuspendLayout();
			// 
			// labelSchimbarePass
			// 
			this->labelSchimbarePass->AutoSize = true;
			this->labelSchimbarePass->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 19.8F, System::Drawing::FontStyle::Italic));
			this->labelSchimbarePass->Location = System::Drawing::Point(144, 9);
			this->labelSchimbarePass->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelSchimbarePass->Name = L"labelSchimbarePass";
			this->labelSchimbarePass->Size = System::Drawing::Size(240, 42);
			this->labelSchimbarePass->TabIndex = 33;
			this->labelSchimbarePass->Text = L"Modify password";
			// 
			// OldPassword
			// 
			this->OldPassword->BackColor = System::Drawing::Color::White;
			this->OldPassword->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"OldPassword.BackgroundImage")));
			this->OldPassword->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->OldPassword->ForeColor = System::Drawing::Color::Black;
			this->OldPassword->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"OldPassword.Icon")));
			this->OldPassword->Location = System::Drawing::Point(121, 55);
			this->OldPassword->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->OldPassword->Name = L"OldPassword";
			this->OldPassword->Size = System::Drawing::Size(281, 54);
			this->OldPassword->TabIndex = 34;
			this->OldPassword->text = L"Old password";
			// 
			// newPassword
			// 
			this->newPassword->BackColor = System::Drawing::Color::White;
			this->newPassword->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"newPassword.BackgroundImage")));
			this->newPassword->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->newPassword->ForeColor = System::Drawing::Color::Black;
			this->newPassword->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"newPassword.Icon")));
			this->newPassword->Location = System::Drawing::Point(121, 117);
			this->newPassword->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->newPassword->Name = L"newPassword";
			this->newPassword->Size = System::Drawing::Size(281, 54);
			this->newPassword->TabIndex = 35;
			this->newPassword->text = L"New password";
			// 
			// LabelEmail
			// 
			this->LabelEmail->AutoSize = true;
			this->LabelEmail->Font = (gcnew System::Drawing::Font(L"Harlow Solid Italic", 19.8F, System::Drawing::FontStyle::Italic));
			this->LabelEmail->Location = System::Drawing::Point(169, 204);
			this->LabelEmail->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->LabelEmail->Name = L"LabelEmail";
			this->LabelEmail->Size = System::Drawing::Size(195, 42);
			this->LabelEmail->TabIndex = 36;
			this->LabelEmail->Text = L"Modify email";
			// 
			// newEmail
			// 
			this->newEmail->BackColor = System::Drawing::Color::White;
			this->newEmail->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"newEmail.BackgroundImage")));
			this->newEmail->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->newEmail->ForeColor = System::Drawing::Color::Black;
			this->newEmail->Icon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"newEmail.Icon")));
			this->newEmail->Location = System::Drawing::Point(121, 250);
			this->newEmail->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->newEmail->Name = L"newEmail";
			this->newEmail->Size = System::Drawing::Size(281, 54);
			this->newEmail->TabIndex = 37;
			this->newEmail->text = L"New email";
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
			this->SaveButton->Location = System::Drawing::Point(70, 384);
			this->SaveButton->Margin = System::Windows::Forms::Padding(5);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(191, 55);
			this->SaveButton->TabIndex = 38;
			this->SaveButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->SaveButton->Click += gcnew System::EventHandler(this, &account::SaveButton_Click);
			// 
			// deleteAccountButton
			// 
			this->deleteAccountButton->ActiveBorderThickness = 1;
			this->deleteAccountButton->ActiveCornerRadius = 20;
			this->deleteAccountButton->ActiveFillColor = System::Drawing::Color::Black;
			this->deleteAccountButton->ActiveForecolor = System::Drawing::Color::White;
			this->deleteAccountButton->ActiveLineColor = System::Drawing::Color::Black;
			this->deleteAccountButton->BackColor = System::Drawing::SystemColors::Control;
			this->deleteAccountButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"deleteAccountButton.BackgroundImage")));
			this->deleteAccountButton->ButtonText = L"Delete account";
			this->deleteAccountButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->deleteAccountButton->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->deleteAccountButton->ForeColor = System::Drawing::Color::Black;
			this->deleteAccountButton->IdleBorderThickness = 1;
			this->deleteAccountButton->IdleCornerRadius = 20;
			this->deleteAccountButton->IdleFillColor = System::Drawing::Color::White;
			this->deleteAccountButton->IdleForecolor = System::Drawing::Color::Black;
			this->deleteAccountButton->IdleLineColor = System::Drawing::Color::Black;
			this->deleteAccountButton->Location = System::Drawing::Point(271, 384);
			this->deleteAccountButton->Margin = System::Windows::Forms::Padding(5);
			this->deleteAccountButton->Name = L"deleteAccountButton";
			this->deleteAccountButton->Size = System::Drawing::Size(191, 55);
			this->deleteAccountButton->TabIndex = 39;
			this->deleteAccountButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->deleteAccountButton->Click += gcnew System::EventHandler(this, &account::deleteAccountButton_Click);
			// 
			// account
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(522, 453);
			this->Controls->Add(this->deleteAccountButton);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->newEmail);
			this->Controls->Add(this->LabelEmail);
			this->Controls->Add(this->newPassword);
			this->Controls->Add(this->OldPassword);
			this->Controls->Add(this->labelSchimbarePass);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"account";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Accout Config";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ newPassword = this->newPassword->text;
	String^ oldPassword = this->OldPassword->text;
	String^ actualPassword = marshal_as<String^>(User::getInstance().getPassword());
	bool modsDone = false;

	if(oldPassword != "Old password" && newPassword != "New password")
	{
		if (oldPassword != actualPassword)
		{
			MessageBox::Show("Incorrect password");
			return;
		}

		if (oldPassword == actualPassword)
			if (oldPassword == newPassword)
			{
				MessageBox::Show("The new password cannot be the old one");
				return;
			}
			else
			{
				ServerIO::getInstance().send_receive("2 " + User::getInstance().getUsername()
					+ " " + msclr::interop::marshal_as<std::string>(oldPassword)
					+ " " + msclr::interop::marshal_as<std::string>(newPassword));

				MessageBox::Show("Password modified successfully");
				modsDone = true;
				User::getInstance().setPassword(marshal_as<std::string>(newPassword));
			}
	}

	String^ newEmail = this->newEmail->text;
	if (newEmail != "New email")
	{
		ServerIO::getInstance().send_receive("3 " + User::getInstance().getUsername()
			+ " " + User::getInstance().getPassword() + " " 
			+ msclr::interop::marshal_as<std::string>(newEmail));
		MessageBox::Show("Email modified successfully");
		User::getInstance().setEmail(marshal_as<std::string>(newEmail));
		modsDone = true;
	}

	if (modsDone)
		this->Close();
}
private: System::Void deleteAccountButton_Click(System::Object^ sender, System::EventArgs^ e) {
	ServerIO::getInstance().send_receive("4 " + to_string(User::getInstance().getUserId()));
	MessageBox::Show("Account deleted successfully");
	this->Close();
	obj->Close();
}
};
}
