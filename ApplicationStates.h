#pragma once

#include "arduino.h"


enum ApplicationStates :byte 
{

	AppStates_None = 0x00,

	AppStates_MainScreen = 0x01,

	AppStates_JustSailMain = 0x02,
	AppStates_JustSailLaps = 0x03,

	AppStates_RaceSetup = 0x04,
	AppSates_RacePreRace = 0x05,
	AppStates_RaceMain = 0x06,

	AppStates_BouyManager = 0x07,

	AppStates_Statistics = 0x08,

	AppStates_GPSData = 0x09,

	AppStates_DeviceSleep = 0x0A
};