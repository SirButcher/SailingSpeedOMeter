#pragma once

enum ApplicationStates :byte {

	AppStates_MainScreen = 0x00,

	AppStates_JustSailMain = 0x01,
	AppStates_JustSailLaps = 0x02,

	AppStates_RaceSetup = 0x03,
	AppSates_RacePreRace = 0x04,
	AppStates_RaceMain = 0x05,

	AppStates_BouyManager = 0x06,

	AppStates_Statistics = 0x07,

	AppStates_GPSData = 0x08,

	AppStates_DeviceSleep = 0x09
};