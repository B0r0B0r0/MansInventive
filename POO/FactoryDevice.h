#pragma once
#include "ServerIO.h"
#include "Bulbs.h"
#include "SurveillanceSystem.h"
#include "Thermostats.h"
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
using namespace msclr::interop;

enum devieType { BULB, THERMOSTAT ,SURVEILLANCESYSTEM };

namespace deviceFactory
{
	inline Device^ getDeviceFromFactory(devieType t,int userID, System::String^ location)
	{
		switch (t)
		{
		case BULB:
			return gcnew Bulbs(10,10,userID,false,location);
			break;
		case THERMOSTAT:
			return gcnew Thermostats(22, 10, userID, false, location);
			break; 
		case SURVEILLANCESYSTEM:
			return gcnew SurveillanceSystem(true, 15, userID, false, location);
			break;
		default:
			break;
		}
	}
}