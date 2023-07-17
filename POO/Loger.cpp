#include "Loger.h"
#include <fstream>
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Drawing;

Loger* Loger::instance = nullptr;

Loger& Loger::getInstance()
{
	if (!Loger::instance)
		Loger::instance = new Loger();

	return *Loger::instance;
}

void Loger::deleteInstance()
{
	if (Loger::instance)
	{
		delete Loger::instance;
		Loger::instance = nullptr;
	}
}

void Loger::log(string str)
{
	ofstream file("log.log", ios::app);
	file << str;
	file.close();
}

void Loger::showLog()
{
	System::String^ fileContent;

	fileContent = File::ReadAllText("log.log");

	RichTextBox^ rtbContent = gcnew RichTextBox();
	rtbContent->Dock = DockStyle::Fill;
	rtbContent->ScrollBars = RichTextBoxScrollBars::Both;
	rtbContent->Text = fileContent;

	Form^ dialog = gcnew Form();
	dialog->Text = "Logs";
	dialog->Icon = SystemIcons::Information;
	dialog->ClientSize = Size(500, 400);
	dialog->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	dialog->Controls->Add(rtbContent);
	dialog->ShowDialog();
	//MessageBox::Show(fileContent, "Continutul fisierului", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
