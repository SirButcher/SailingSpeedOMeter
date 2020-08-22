// ButtonHandler.h

#ifndef _BUTTONHANDLER_h
#define _BUTTONHANDLER_h

#include "PCA9536.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


namespace ScreenButtonHandler {

	const int minimumMillisecForButtonPress = 25;

	typedef enum :byte
	{
		// Button IO0
		ScreenButton_Confirm = 0,
		// Button IO1
		ScreenButton_Cancel = 1,
		// Button IO2
		ScreenButton_Up = 2,
		// Button IO3
		ScreenButton_Down = 3
	} ScreenButton;

	typedef enum :byte {

		ScreenButtonStatus_None = 0,

		// The button pressed just now, it was unpressed previously.
		ScreenButtonStatus_JustPressed = 1,

		// The button was either pressed or unpressed last time
		// but it is pressed now (user holding it down).
		ScreenButtonStatus_Pressed = 2,

		// The button was pressed, but it is released now.
		ScreenButtonStatus_Clicked = 3,

	} ButtonStatus;


	class ButtonHandler {

		public:

			ButtonHandler();

			bool IsDeviceWorking();
			ButtonStatus GetButtonState(ScreenButton button);
			void UpdateButtonStatus(long currentTime);

		private:
			long lastCheckTime;

			bool isDeviceWorking;

			PCA9536 ioExtender;

			ButtonStatus currentButtonStatus[4] = { ScreenButtonStatus_None, ScreenButtonStatus_None, ScreenButtonStatus_None, ScreenButtonStatus_None };
			byte previousButtonState[4] = { 0, 0, 0, 0 };
	};
}

using namespace ScreenButtonHandler;

#endif

