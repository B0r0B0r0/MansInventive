#include "User.h"

User* User::instance = nullptr;

User& User::getInstance(string username, string password, string email, bool IsAdmin,int userId)
{
    if (!User::instance)
    {
        User::instance = new User(username,password,email,IsAdmin,userId);
    }
    return (*User::instance);
}

User& User::getInstance()
{
    if (!User::instance)
    {
        User::instance = new User();
    }
    return (*User::instance);
}

void User::destroyInstance()
{
    if (User::instance != nullptr)
    {
        delete User::instance;
        User::instance = nullptr;
    }
}