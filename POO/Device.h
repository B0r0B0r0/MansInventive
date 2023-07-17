#pragma once
#include <string>
using namespace std;

public ref class Device
{
private:
    bool isOn;
    int userId;
    System::String^ location;

public:
    Device()
    {
        isOn = true;
        userId = 0;
        location = "";
    }

    Device(bool status, int userId,System::String^ location)
    {
        this->isOn = status;
        this->userId = userId;
        this->location = location;
    }

    ~Device()
    {
        isOn = false;
        userId = 0;
        location = "";
    }

    void ToggleOnOff()
    {
        if (isOn)
            isOn = false;
        else isOn = true;
    }

    bool getStatus()
    {
        return isOn;
    }

    int getUserId()
    {
        return this->userId;
    }

    System::String^ getLocation()
    {
        return this->location;
    }

    virtual string getDeviceType() = 0;
};