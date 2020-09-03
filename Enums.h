#pragma once

enum ScreenButton :byte
{
	// Button IO0
	ScreenButton_Confirm = 0x00,
	// Button IO1
	ScreenButton_Cancel = 0x01,
	// Button IO2
	ScreenButton_Up = 0x02,
	// Button IO3
	ScreenButton_Down = 0x03
};

enum ButtonStatus :byte
{

	ScreenButtonStatus_None = 0x00,

	// The button pressed just now, it was unpressed previously.
	ScreenButtonStatus_JustPressed = 0x01,

	// The button was either pressed or unpressed last time
	// but it is pressed now (user holding it down).
	ScreenButtonStatus_Pressed = 0x02,

	// The button was pressed, but it is released now.
	ScreenButtonStatus_Clicked = 0x03,

};

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