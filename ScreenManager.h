// ScreenManager.h

#pragma once

#ifndef _SCREENMANAGER_h
#define _SCREENMANAGER_h

#include "Pins.h"
#include "Enums.h"
#include <LiquidCrystal.h>

namespace ScreenManager 
{

	const char emptyScreenChar = ' ';

	class ScreenController 
	{

	public:

		void Init(int _characterCount, int _lineCount);

		// Display a hard-coded text
		void DisplayText(const char text[20], int cursorX, int cursorY);

		// Load a data from the Flash memory and display it on the screen.
		void DisplayText(long flashAddress, int cursorX, int cursorY);

		void ClearLine(int cursorY);

	private:
		int characterCount;
		int lineCount;

		char screenBuffer[20];
		bool screenBufferIsClearLine = false;
		LiquidCrystal* lcd;
	};
}

using namespace ScreenManager;

#endif

