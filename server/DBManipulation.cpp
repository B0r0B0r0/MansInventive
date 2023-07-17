#include "DBManipulation.h"
#include <sstream>


DBManipulation* DBManipulation::instance = nullptr;

DBManipulation::DBManipulation()
{
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;
}

SQLWCHAR* DBManipulation::stringtoSQLWCHAR(const string& str)
{
    int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    SQLWCHAR* buffer = new SQLWCHAR[length];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, length);
    return buffer;
}

DBManipulation* DBManipulation::getInstance()
{
    if (instance == nullptr)
        instance = new DBManipulation;
    return instance;
}

void DBManipulation::destroyInstance()
{
    delete instance;
}

void DBManipulation::initializeConnection()
{
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        throw (new MyException(1, "Eroare la SQLAllocHandle"));
    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        throw (new MyException(1, "Eroare la SQLSetEnvAttr"));
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        throw (new MyException(1, "Eroare la SQLALLocHandle"));
    switch (SQLDriverConnect(sqlConnHandle,
        NULL,
        //(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
        (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=DESKTOP-DLEFTN6\\MANSINVENTIVE;DATABASE=SmartHome;UID=cppAdmin;PWD=parolabengoasa;",
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT)) {
    case SQL_SUCCESS:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_SUCCESS_WITH_INFO:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_INVALID_HANDLE:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        throw (new MyException(2, "Eroare la conectarea cu serverul"));
    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        throw (new MyException(2, "Eroare la conectarea cu serverul"));
    default:
        break;
    }

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        throw (new MyException(1, "Eroare la SQLALLocHandle"));
}

void DBManipulation::destroyConnection()
{
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

string DBManipulation::verifyUser(string credentials_p)
{
    string user, parola;
    size_t pos = 0;

    // extrag username-ul
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);

    // extrag parola
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    parola = credentials_p.substr(0, pos);
    SQLRETURN retcode;
    SQLCHAR username[50];
    SQLCHAR password[255];
    SQLLEN userLenght = 0;
    SQLLEN passLenght = 0;


    string strquery = "Select * from Utilizatori where username = '" + user + "'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);

    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }


    retcode = SQLBindCol(sqlStmtHandle, 2, SQL_C_CHAR, &username, sizeof(username), &userLenght);
    retcode = SQLBindCol(sqlStmtHandle, 3, SQL_C_CHAR, &password, sizeof(password), &passLenght);

    SQLFetch(sqlStmtHandle);
  

    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    string usernameStr(reinterpret_cast<const char*>(username), userLenght);
    string passwordstr(reinterpret_cast<const char*>(password), passLenght);

    if (usernameStr != user)
        return "Not in BD";
    if (passwordstr != parola)
        return "Wrong Password"; //se afla in BD, dar nu a introdus parola corect
    
    return "Conectat"; // Exista in BD
}

string DBManipulation::loginUser(string credentials_p)
{
    string user, parola;
    size_t pos = 0;

    // extrag username-ul
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);

    // extrag parola
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    parola = credentials_p.substr(0, pos);
  
    SQLRETURN retcode;
    SQLCHAR email[255];
    SQLINTEGER statusAdmin = 0;
    SQLINTEGER userId = 0;
    SQLLEN emailLenght = 0;
    string strquery = "Select * from Utilizatori where username = '" + user + "' and password = '" + parola + "'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    retcode = SQLBindCol(sqlStmtHandle, 4, SQL_C_CHAR, &email, sizeof(email), &emailLenght);
    retcode = SQLBindCol(sqlStmtHandle, 1, SQL_C_LONG, &userId, sizeof(userId), NULL);
    retcode = SQLBindCol(sqlStmtHandle, 5, SQL_C_LONG, &statusAdmin, sizeof(statusAdmin), NULL);
    SQLFetch(sqlStmtHandle);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);

    string emailstr(reinterpret_cast<const char*>(email), emailLenght);

    stringstream ss;
    ss << userId;
    string userIdstr = ss.str();
    ss.str("");
    ss << statusAdmin;
    string statusAdminstr = ss.str();
    string response = userIdstr + " " + emailstr + " " + statusAdminstr;
    return response;
}

bool DBManipulation::registerUser(string credentials_p)
{
    string user, parola, email, statusAdmin;
    size_t pos = 0;

    // extrag username-ul
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);

    // extrag parola
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    parola = credentials_p.substr(0, pos);

    // extrag email-ul
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    email = credentials_p.substr(0, pos);

    // extrag statusAdmin
    credentials_p = credentials_p.substr(pos + 1);
    statusAdmin = credentials_p;

    // execut query-ul
    string strquery = "EXEC Register_User '" + user + "', '"+parola+"', '"+email+"', "+statusAdmin+"";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }
    return true;

}

string DBManipulation::insertDispozitiv(string credentials_p)
{
    string user, denumire, locatie, parametru1,parametru2;
    size_t pos = 0;

    // extrag username-ul
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);

    // extrag denumirea
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    denumire = credentials_p.substr(0, pos);

    // extrag locatia
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    locatie = credentials_p.substr(0, pos);

    // extrag primul parametru
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    parametru1 = credentials_p.substr(0, pos);

    //extrag al doilea parametru
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    parametru2 = credentials_p.substr(0, pos);
    // verific daca e deja in bd
    string strquery = "exec Register_Dispozitiv '"+user+"', '"+denumire+"', '"+locatie+"', "+parametru1+", "+parametru2;
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        return  (string)"Exista deja in BD";
    } 
    return (string)"Adaugat cu succes";
    
}

void DBManipulation::modifyParola(string credentials_p)
{
    // Izolez parola noua si user-ul
    string user;
    size_t pos = 0;
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);
    credentials_p = credentials_p.substr(pos + 1);

    pos = credentials_p.find(" ");
    credentials_p = credentials_p.substr(pos + 1);
    
    // Actualizez baza de date
    string strquery = "EXEC Modify_Password '"+user+"', '"+credentials_p+"'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }

}

void DBManipulation::modifyEmail(string credentials_p)
{
    // Izolez emailul si user-ul
    string user;
    size_t pos = 0;
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);
    credentials_p = credentials_p.substr(pos + 1);

    pos = credentials_p.find(" ");
    credentials_p = credentials_p.substr(pos + 1);

    // Actualizez baza de date
    string strquery = "EXEC Modify_Email '" + user + "', '" + credentials_p + "'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }

}

void DBManipulation::deleteUser(string credentials_p)
{
    string strquery = "exec Delete_User " + credentials_p;
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }

}

void DBManipulation::deleteDevice(string credentials_p)
{
    string  denumire, locatie;
    size_t pos = 0;

    // extrag username-ul
    pos = credentials_p.find(" ");
    denumire = credentials_p.substr(0, pos);

    // extrag denumirea
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    locatie = credentials_p.substr(0, pos);

    string strquery = "exec Delete_Dispozitiv '" + denumire+"', '"+locatie+"'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }


}

vector<string> DBManipulation::getDisp(string credentials_p)
{
    vector<string> finalResult;
    string strquery = "exec Get_Dispozitive '"+credentials_p+"'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);

    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }

    SQLCHAR idUser[255], username[255],denumire[255], locatie[255], parametru1[255], parametru2[255], status[255];
    SQLLEN lenghtId, lenghtUsername,lenghtDenumire, lenghtLocatie, lenghtParametru1, lenghtParametru2, lenghStatus;

    SQLBindCol(sqlStmtHandle, 1, SQL_C_CHAR, idUser, 255, &lenghtId);
    SQLBindCol(sqlStmtHandle, 2, SQL_C_CHAR, username, 255, &lenghtUsername);
    SQLBindCol(sqlStmtHandle, 3, SQL_C_CHAR, denumire, 255, &lenghtDenumire);
    SQLBindCol(sqlStmtHandle, 4, SQL_C_CHAR, locatie, 255, &lenghtLocatie);
    SQLBindCol(sqlStmtHandle, 5, SQL_C_CHAR, parametru1, 255, &lenghtParametru1);
    SQLBindCol(sqlStmtHandle, 6, SQL_C_CHAR, parametru2, 255, &lenghtParametru2);
    SQLBindCol(sqlStmtHandle, 7, SQL_C_CHAR, status, 255, &lenghStatus);




    // Loop through the result set and print the values of each row
    while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
    {
        string idStr(reinterpret_cast<const char*>(idUser), lenghtId);
        string usernameStr(reinterpret_cast<const char*>(username), lenghtUsername);
        string denumireStr(reinterpret_cast<const char*>(denumire), lenghtDenumire);
        string locatieStr(reinterpret_cast<const char*>(locatie), lenghtLocatie);
        string parametru1Str(reinterpret_cast<const char*>(parametru1), lenghtParametru1);
        string parametru2Str(reinterpret_cast<const char*>(parametru2), lenghtParametru2);
        string statusStr(reinterpret_cast<const char*>(status), lenghStatus);
        string result = idStr + " " + usernameStr + " " + denumireStr + " " + locatieStr;
        result += " " + parametru1Str + " " + parametru2Str + " " + statusStr;
        finalResult.push_back(result);
    }

    return finalResult;
}

string DBManipulation::findDevice(string credentials_p)
{
    string denumire, locatie;
    size_t pos = 0;

    // extrag denumirea
    pos = credentials_p.find(" ");
    denumire = credentials_p.substr(0, pos);

    // extrag locatia
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    locatie = credentials_p.substr(0, pos);


    string strquery = "Select * from Dispozitive where denumire = '" +denumire+"' and locatie ='"+locatie+"'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);

    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }

    SQLCHAR pa1[255];
    SQLCHAR pa2[255];
    SQLLEN pa1len = 0;
    SQLLEN pa2len = 0;

    retcode = SQLBindCol(sqlStmtHandle, 2, SQL_C_CHAR, &pa1, sizeof(pa1), &pa1len);
    retcode = SQLBindCol(sqlStmtHandle, 3, SQL_C_CHAR, &pa2, sizeof(pa2), &pa2len);

    SQLFetch(sqlStmtHandle);


    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    string parametru1(reinterpret_cast<const char*>(pa1), pa1len);
    string parametru2(reinterpret_cast<const char*>(pa2), pa2len);

    string response = denumire + " " + locatie + " " + parametru1 + " " + parametru2;
    return response;
}

void DBManipulation::modifyDevice(string credentials_p)
{
    string denumire, locatie, param1, param2;
    size_t pos = 0;

    // extrag denumirea
    pos = credentials_p.find(" ");
    denumire = credentials_p.substr(0, pos);

    // extrag locatia
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    locatie = credentials_p.substr(0, pos);

    // extrag primul parametru
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    param1 = credentials_p.substr(0, pos);

    // extrag al doilea parametru
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    param2 = credentials_p.substr(0, pos);

    string strquery = "exec Modify_Dispozitiv '" + denumire + "', '" + locatie + "', '"+ param1 + "', '"+param2+"'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }

}

void DBManipulation::addAsoc(string credentials_p)
{
    string user,denumire, locatie;
    size_t pos = 0;

    // extrag denumirea
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);

    // extrag locatia
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    denumire = credentials_p.substr(0, pos);

    // extrag primul parametru
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    locatie = credentials_p.substr(0, pos);

    string strquery = "exec Adauga_Asociere '"+user+"', '" + denumire + "', '" + locatie + "'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }
}

void DBManipulation::deleteAsoc(string credentials_p)
{
    string user, denumire, locatie;
    size_t pos = 0;

    // extrag denumirea
    pos = credentials_p.find(" ");
    user = credentials_p.substr(0, pos);

    // extrag locatia
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    denumire = credentials_p.substr(0, pos);

    // extrag primul parametru
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    locatie = credentials_p.substr(0, pos);

    string strquery = "exec Scoatere_Asociere '" + user + "', '" + denumire + "', '" + locatie + "'";
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }
}

void DBManipulation::modifyStatus(string credentials_p, string status)
{
    string denumire, locatie;
    size_t pos = 0;

    // extrag denumirea
    pos = credentials_p.find(" ");
    denumire = credentials_p.substr(0, pos);

    // extrag locatia
    credentials_p = credentials_p.substr(pos + 1);
    pos = credentials_p.find(" ");
    locatie = credentials_p.substr(0, pos);


    string strquery = "exec Modifica_Status '" + denumire + "', '" + locatie + "', "+status;
    SQLWCHAR* query = stringtoSQLWCHAR(strquery);
    SQLRETURN retcode = SQLExecDirect(sqlStmtHandle, query, SQL_NTS);
    SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode) {
        cout << "Error querying SQL Server";
        cout << "\n";
        throw(new MyException(3, "Eroare la parsarea query-ului"));
    }
}
