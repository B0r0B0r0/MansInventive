#pragma once
#include "Device.h"

public ref class Bulbs : public Device
{
private:
    int brightness;
    int colorTemperature;

public:
    Bulbs()
    {
        brightness = 0;
        colorTemperature = 0;
    }

    Bulbs(int brightness, int colorTemperature,int userId,bool status, System::String^ location):
    Device(status,userId,location)
    {
        this->brightness = brightness;
        this->colorTemperature = colorTemperature;
    }

    ~Bulbs()
    {
        this->brightness = 0;
        this->colorTemperature = 0;
    }

    void SetBrightness(int value)
    {
        this->brightness = value;
    }

    void SetColorTemperature(int value)
    {
        this->colorTemperature = value;
    }

    int getBrightness()
    {
        return this->brightness;
    }

    int getColorTemperature()
    {
        return this->colorTemperature;
    }

    virtual string getDeviceType() override
    {
        return "Bec";
    }
};