#include"DBManipulation.h"
#include"Connection.h"
#include<Windows.h>

#define ci Connection::getInstance()
#define dbi DBManipulation::getInstance()


int main()
{
	ci->createConnection();
	//system("start C:\\Users\\Ayeleen\\source\\repos\\POOProiectBec\\x64\\Debug\\POOProiectDispozitiv.exe 1 1 1 1 1");

	
	while (true)
	{
		ci->waitForConnection();
		ci->receiveMessageFromClient();
	}
	
	return 1;
}