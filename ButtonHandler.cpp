
// Created: 22/08/2020

#include "ButtonHandler.h"
#include "ButtonStatus.h"
#include "ScreenButtons.h"

void ScreenButtonHandler::ButtonHandler::Init()
{
	// Set up the variables:
	isDeviceWorking = false;

	// Check if the device even connected / working:
	// Code 0 means the connection was succesful.
	isDeviceWorking = ioExtender.ping() == 0;

	if (isDeviceWorking == false)
	{
		// Our device is not working!
		// Abort and let the user know to bin the whole thing.
		return;
	}

	// Reset our extender to set up a clean state:
	ioExtender.reset();

	// Set up our pins as an input pins:
	ioExtender.setMode(IO0, IO_INPUT);
	ioExtender.setMode(IO1, IO_INPUT);
	ioExtender.setMode(IO2, IO_INPUT);
	ioExtender.setMode(IO3, IO_INPUT);

	// Wait a little, then do another test:
	delay(10);
	isDeviceWorking = ioExtender.ping() == 0;

	if (isDeviceWorking)
		UpdateButtonStatus();
}

bool ScreenButtonHandler::ButtonHandler::IsDeviceWorking()
{
	return isDeviceWorking;
}

ButtonStatus ScreenButtonHandler::ButtonHandler::GetButtonState(ScreenButton button)
{
	return currentButtonStatus[button];
}

void ScreenButtonHandler::ButtonHandler::UpdateButtonStatus()
{
	// This method shouldn't be run too fast, or we couldn't handle the button bouncing.
	// The main loop should wait at least a little until the button itself settles
	// physically into it's actual state.

	// A button is considered pressed if it was not pressed last time
	// but pressed now.

	byte i;
	for (i = 0; i < 4; i++)
	{
		pin_t currentBtn = static_cast<pin_t>(i);

		// Get the current status:
		byte buttonStatus = ioExtender.getState(currentBtn);

		// Iterate throught the possible states:
		if (buttonStatus == 0 && previousButtonState[i] == 0) // Nothing happened
			currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_None;
		else if (buttonStatus == 1 && previousButtonState[i] == 0) // It is pressed NOW, but was unpressed previously
			currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_JustPressed;
		else if (buttonStatus == 1 && previousButtonState[i] == 1) // Was pressed previosly and still pressed
			currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_Pressed;
		else if (buttonStatus == 0 && previousButtonState[i] == 1) // Released now, but was pressed previously
			currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_Clicked;

		// And finally save the current state as the previous one
		// for the next time when we check it.
		previousButtonState[i] = buttonStatus;
	}
}
