// ScreenManager.h

#pragma once

#ifndef _SCREENMANAGER_h
#define _SCREENMANAGER_h

#include "Pins.h"
#include "Enums.h"
#include "MemoryHandler.h"
#include <LiquidCrystal.h>

namespace ScreenManager 
{

	const char emptyScreenChar = ' ';

	class ScreenController 
	{

	public:

		void Init(MemoryController* _memoryController, int _characterCount, int _lineCount);

		// Display a hard-coded text
		void DisplayText(const char text[20], int cursorX, int cursorY);

		// Load a data from the Flash memory and display it on the screen.
		void DisplayText(ScreenMessage address, int cursorX, int cursorY);

		void ClearWholeScreen();

		// Fill a line with spaces.
		void ClearLine(int cursorY);

	private:
		int characterCount;
		int lineCount;

		char screenBuffer[20];
		bool screenBufferIsClearLine = false;
		LiquidCrystal* lcd;
		MemoryController* memoryController;
	};
}

using namespace ScreenManager;

#endif

