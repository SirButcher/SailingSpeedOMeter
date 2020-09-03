
#include "ScreenManager.h"


void ScreenManager::ScreenController::Init(int _characterCount, int _lineCount)
{
	characterCount = _characterCount;
	lineCount = _lineCount;

	lcd = new LiquidCrystal(Pin_Screen_RS, Pin_Screen_EN, Pin_Screen_D4, Pin_Screen_D5, Pin_Screen_D6, Pin_Screen_D7);

	// Initialize the screen's starting params
	lcd->begin(characterCount, lineCount); // set up number of columns and rows
	lcd->clear();
	lcd->display();
}

void ScreenManager::ScreenController::DisplayText(const char text[20], int cursorX, int cursorY)
{
	lcd->setCursor(cursorX, cursorY);
	lcd->print(text);
}

void ScreenManager::ScreenController::DisplayText(long flashAddress, int cursorX, int cursorY)
{
	//screenBufferIsClearLine = false;
}

void ScreenManager::ScreenController::ClearLine(int cursorY)
{
	/*
	if (!screenBufferIsClearLine)
	{
		int i;
		for (i = 0; i < 20; i++)
			screenBuffer[i] = emptyScreenChar;

		screenBufferIsClearLine = true;
	}

	lcd.setCursor(0, cursorY);
	lcd.print(screenBuffer);
	*/
}