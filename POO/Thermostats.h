#pragma once
#include "Device.h"

public ref class Thermostats : public Device
{
private:
    int temperature;
    int humidity;

public:
    Thermostats()
    {
        temperature = 0;
        humidity = 0;
    }

    Thermostats(int temperature, int humidity, int userId, bool status, System::String^ location) :
        Device(status, userId, location)
    {
        this->temperature = temperature;
        this->humidity = humidity;
    }

    ~Thermostats()
    {
        this->temperature = 0;
        this->humidity = 0;
    }

    void Settemperature(int value)
    {
        this->temperature = value;
    }

    void Sethumidity(int value)
    {
        this->humidity = value;
    }

    int getTemperature()
    {
        return this->temperature;
    }

    int getHumidity()
    {
        return this->humidity;
    }

    virtual string getDeviceType() override
    {
        return "Termostat";
    }
};

