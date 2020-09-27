#pragma once

#ifndef _MAINMENU_H
#define _MAINMENU_H

// Enums and variables
#include "ApplicationStates.h"
#include "ScreenButtons.h"

// Program module libs
#include "ButtonHandler.h"
#include "ScreenManager.h"


namespace MenuSystem
{

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
		ButtonHandler* buttonHandler;
		ScreenController* screenController;


	};

}

using namespace MenuSystem;

#endif