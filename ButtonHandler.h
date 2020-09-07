// ButtonHandler.h

#pragma once


#ifndef _BUTTONHANDLER_h
#define _BUTTONHANDLER_h

#include "PCA9536.h"
#include "Enums.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


namespace ScreenButtonHandler {

	const int minimumMillisecForButtonPress = 5;

	class ButtonHandler {

		public:

			void Init();

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

