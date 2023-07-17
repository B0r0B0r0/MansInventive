#pragma once

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "MyException.h"


using namespace std;

class DBManipulation
{
	static DBManipulation* instance;
	DBManipulation();
	~DBManipulation() {}

	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

	SQLWCHAR* stringtoSQLWCHAR(const string& str);


public:
	static DBManipulation* getInstance();
	static void destroyInstance();
	void initializeConnection();
	void destroyConnection();


	string verifyUser(string credentials_p);
	string loginUser(string credentials_p);
	bool registerUser(string credentials_p);
	string insertDispozitiv(string credentials_p);
	void modifyParola(string credentials_p);
	void modifyEmail(string credentials_p);
	void deleteUser(string credentials_p);
	void deleteDevice(string credentials_p);
	vector<string> getDisp(string credentials_p);
	string findDevice(string credentials_p);
	void modifyDevice(string credentials_p);
	void addAsoc(string credentials_p);
	void deleteAsoc(string credentials_p);
	void modifyStatus(string credentials_p, string status);

};

