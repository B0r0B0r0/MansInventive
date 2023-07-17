#pragma once
#include "Device.h"

public ref class SurveillanceSystem : public Device
{
private:
    bool isRecording;
    int sensitivity;

public:
    SurveillanceSystem()
    {
        isRecording = false;
        sensitivity = 0;
    }

    SurveillanceSystem(bool isRecording, int sensitivity, int userId, bool status, System::String^ location) :
        Device(status, userId, location)
    {
        this->isRecording = isRecording;
        this->sensitivity = sensitivity;
    }

    ~SurveillanceSystem()
    {
        this->isRecording = false;
        this->sensitivity = 0;
    }

    void SetIsRecording(bool value)
    {
        this->isRecording = value;
    }

    void SetSensitivity(int value)
    {
        this->sensitivity = value;
    }

    bool getIsRecording()
    {
        return this->isRecording;
    }

    int getSensitivity()
    {
        return this->sensitivity;
    }

    virtual string getDeviceType() override
    {
        return "Camera";
    }
};

