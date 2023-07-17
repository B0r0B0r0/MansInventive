#pragma hdrstop
#pragma once
#include <string>
using namespace std;
using namespace System;

class User
{
private:
    static User* instance;
    string username;
    string password;
    string email;
    int userId;
    bool IsAdmin;

    User()
    {
        this->username = "";
        this->password = "";
        this->email = "";
        this->IsAdmin = false;
        userId = 0;
    }

    User(string username, string password, string email, bool IsAdmin,int userId)
    {
        this->username = username;
        this->password = password;
        this->email = email;
        this->IsAdmin = IsAdmin;
        this->userId = userId;
    }

    ~User()
    {
        this->username = "";
        this->password = "";
        this->email = "";
        this->IsAdmin = false;
        userId = 0;
    }

public:
    static User& getInstance(string username, string password, string email, bool IsAdmin,int userId);
    static User& getInstance();
    static void destroyInstance();

    void setPassword(string new_password)
    {
        this->password = new_password;
    }

    void setEmail(string new_email)
    {
        this->email = new_email;
    }

    string getPassword()
    {
        return this->password;
    }

    string getEmail()
    {
        return this->email;
    }

    string getUsername()
    {
        return this->username;
    }

    int getUserId()
    {
        return this->userId;
    }

    bool isUserAdmin()
    {
        return this->IsAdmin;
    }
};