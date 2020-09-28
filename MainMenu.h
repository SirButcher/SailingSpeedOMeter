#pragma once

#ifndef _MAINMENU_H
#define _MAINMENU_H

#include <Arduino.h>

// Enums and variables
#include "ApplicationStates.h"
#include "ScreenButtons.h"
#include "ScreenMessages.h"

// Program module libs
#include "ButtonHandler.h"
#include "ScreenManager.h"


namespace MenuSystem
{
	const uint8_t screenMainMenu_menuItemCount = 6;

	class MainMenu
	{

	public:

		void Init(ButtonHandler* _buttonHandler, ScreenController* _screenController);

		// Change to the current screen type, and get ready for the main loop
		void TakeOver();

		// Run and handle the app. Will return with True if should switch
		// to the newState
		bool MainLoop(ApplicationStates* newState);

	private:

		void UpdateMenu(uint8_t selectedMenu, uint8_t menuToDisplayFrom);

		ButtonHandler* buttonHandler;
		ScreenController* screenController;

		ScreenMessage menuOptions[screenMainMenu_menuItemCount];
	};

}

using namespace MenuSystem;

#endif