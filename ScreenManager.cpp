
#include "ScreenManager.h"



void ScreenManager::ScreenController::Init(MemoryController* _memoryController)
{
	memoryController = _memoryController;

	// Initialize the screen's starting params
	lcd.begin(screenLineCharacterCount, screenLineCount); // set up number of columns and rows

	// Turn off every not-needed function:
	lcd.noAutoscroll();
	lcd.noBlink();
	lcd.noCursor();

	//Clear the screen, and set the display value (in case it is a new screen)
	lcd.clear();
	lcd.display();

	delay(10);
}

void ScreenManager::ScreenController::ClearWholeScreen()
{
	lcd.clear();
}


void ScreenManager::ScreenController::DisplayText(const char text[20], uint8_t lenght, uint8_t cursorX, uint8_t cursorY)
{
	lcd.setCursor(cursorX, cursorY);
	lcd.write(text, lenght);
}

void ScreenManager::ScreenController::DisplayText(const char text[20], uint8_t cursorX, uint8_t cursorY)
{
	DisplayText(text, 20, cursorX, cursorY);
}

void ScreenManager::ScreenController::DisplayText(ScreenMessage address, uint8_t cursorX, uint8_t cursorY)
{
	DisplayText(memoryController->GetScreenMessage(address), 20, cursorX, cursorY);
}

void ScreenManager::ScreenController::DisplayText(ScreenMessage address, uint8_t lenght, uint8_t cursorX, uint8_t cursorY)
{
	DisplayText(memoryController->GetScreenMessage(address), lenght, cursorX, cursorY);
}

void ScreenManager::ScreenController::ClearLine(int cursorY)
{
	if (!screenBufferIsClearLine)
	{
		int i;
		for (i = 0; i < 20; i++)
			screenBuffer[i] = emptyScreenChar;

		screenBufferIsClearLine = true;
	}

	lcd.setCursor(0, cursorY);
	lcd.print(screenBuffer);
}
