
// Created: 22/08/2020


#include "ButtonHandler.h"

ScreenButtonHandler::ButtonHandler::ButtonHandler()
{
	// Set up the variables:
	lastCheckTime = -1; // To ensure a forced first time check
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
}

bool ScreenButtonHandler::ButtonHandler::IsDeviceWorking()
{
	return isDeviceWorking;
}

ButtonStatus ScreenButtonHandler::ButtonHandler::GetButtonState(ScreenButton button)
{
	return currentButtonStatus[button];
}

void ScreenButtonHandler::ButtonHandler::UpdateButtonStatus(long currentTime)
{
	// We only want to check the current statuses if the elapsed time
	// more than our threshold (to handle button bouncing)

	if (currentTime - lastCheckTime > minimumMillisecForButtonPress)
	{
		// OK, enough time is elapsed!
		lastCheckTime = currentTime;

		// a button is considered pressed if it was not pressed last time
		// but pressed now.

		byte i;
		for (i = 0; i < 4; i++)
		{
			pin_t currentBtn = static_cast<pin_t>(i);

			// Get the current status:
			byte buttonStatus = ioExtender.getState(currentBtn);

			// Iterate throught the possible states:
			if (buttonStatus == 0 && previousButtonState[i] == 0)
				currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_None;
			else if (buttonStatus == 1 && previousButtonState[i] == 0)
				currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_JustPressed;
			else if (buttonStatus == 1 && previousButtonState[i] == 1)
				currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_Pressed;
			else if (buttonStatus == 0 && previousButtonState[i] == 1)
				currentButtonStatus[i] = ButtonStatus::ScreenButtonStatus_Clicked;

			// And finally save the current state as the previous one
			// for the next time when we check it.
			previousButtonState[i] = buttonStatus;
		}
	}
}
