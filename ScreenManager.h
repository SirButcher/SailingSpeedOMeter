// ScreenManager.h

#pragma once

#ifndef _SCREENMANAGER_h
#define _SCREENMANAGER_h

#include <Arduino.h>

#include "Pins.h"

#include "MemoryHandler.h"
#include <LiquidCrystal.h>

namespace ScreenManager 
{
	const uint8_t screenLineCharacterCount = 20;
	const uint8_t screenLineCount = 4;

	class ScreenController 
	{

	public:

		void Init(MemoryController* _memoryController);

		void ClearWholeScreen();

		// Display a hard-coded text
		void DisplayText(const char text[20], uint8_t cursorX, uint8_t cursorY);

		// Display part of a hard-coded text with given lenght
		void DisplayText(const char text[20], uint8_t lenght, uint8_t cursorX, uint8_t cursorY);

		// Load a data from the Flash memory and display it on the screen.
		void DisplayText(ScreenMessage address, uint8_t cursorX, uint8_t cursorY);

		// Load a data from the Flash memory and display selected characters from it on the screen.
		void DisplayText(ScreenMessage address, uint8_t lenght, uint8_t cursorX, uint8_t cursorY);

		// Fill a line with spaces.
		void ClearLine(int cursorY);

	private:

		int characterCount;
		int lineCount;

		char screenBuffer[20];
		bool screenBufferIsClearLine = false;

		LiquidCrystal lcd = LiquidCrystal(Pin_Screen_RS, Pin_Screen_EN, Pin_Screen_D4, Pin_Screen_D5, Pin_Screen_D6, Pin_Screen_D7);
		MemoryController* memoryController;

	};
}

using namespace ScreenManager;

#endif

