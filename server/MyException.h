#pragma once
#include <string>

using namespace std;

class MyException
{
	int errorCode;
	string errorMessage;

public:
	MyException(int errorCode_p, string errorMessage_p) : errorCode(errorCode_p), errorMessage(errorMessage_p) {}
	~MyException() { errorCode = 0; string errorMessage = ""; }
	int getErrorCode() { return errorCode; }
	string getErrorMessage() { return errorMessage; }
};

