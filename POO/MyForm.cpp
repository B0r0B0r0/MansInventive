#include "MyForm.h"
#include "ServerIO.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main()
{
	ServerIO::getInstance().connect_to_server();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	POO::MyForm  form;
	Application::Run(%form);
	ServerIO::getInstance().send_receive("client");

}