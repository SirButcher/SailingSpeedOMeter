#include "MainMenu.h"


void MenuSystem::MainMenu::Init(ButtonHandler* _buttonHandler, ScreenController* _screenController)
{
    buttonHandler = _buttonHandler;
    screenController = _screenController;
}

void MenuSystem::MainMenu::TakeOver()
{
    // We took over the WORLD!

    // First, clear the whole screen.
    screenController -> ClearWholeScreen();


}

bool MenuSystem::MainMenu::MainLoop(ApplicationStates* newState)
{
    return false;
}


void TakeOver()
{

}

bool MainLoop(ApplicationStates* newState) {




    return false;
}
