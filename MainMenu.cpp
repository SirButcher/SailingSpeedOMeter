#include "MainMenu.h"


void MainMenu::Init(ButtonHandler* _buttonHandler, ScreenController* _screenController)
{
    buttonHandler = _buttonHandler;
    screenController = _screenController;

    menuOptions[0] = ScreenMessage_Menu_JustSail;
    menuOptions[1] = ScreenMessage_Menu_RaceMain;
    menuOptions[2] = ScreenMessage_Menu_Statistics;
    menuOptions[3] = ScreenMessage_Menu_GPSDataMain;
    menuOptions[4] = ScreenMessage_Menu_BouySystem;
    menuOptions[5] = ScreenMessage_Menu_DeviceSleep;
}

void MainMenu::TakeOver()
{
    // We took over the WORLD!

    // First, clear the whole screen.
    screenController -> ClearWholeScreen();

    // OK, now we have our screen nice and ready.
    // We have to write the menu options on it first
    // And select the first one.

    UpdateMenu(0, 0);
}

void MainMenu::UpdateMenu(uint8_t selectedMenu, uint8_t menuToDisplayFrom)
{
    // This method only will be called when:
    // 1. User navigate to the main menu
    // 2. User press the up or down buttons

    uint8_t i;
    for (i = 0; i < screenMainMenu_menuItemCount; i++)
    {
        //if (i + menuToDisplayFrom == selectedMenu)
        if(i == 0)
        {
            // This menu is the one where we have the cursor currently!
            // Before we draw the line, draw the cursor first.
            screenController->DisplayText(ScreenMessage_Spec_SelectorLeft, 0, i);
        }

        if (i == ScreenManager::screenLineCount)
            break;

        screenController->DisplayText(menuOptions[i], 2, i);
    }
}

bool MainMenu::MainLoop(ApplicationStates* newState)
{
    static uint8_t selectedMenu = 0;
    static uint8_t menuToDisplayFrom = 0;


    return false;
}

