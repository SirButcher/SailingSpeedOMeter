/*
 Name:		SailingSpeedOMeter.ino
 Created:	25/06/2020 02:17:23 PM
 Author:	Gabriel Butcher
*/

// Sub-system libs
#include <Wire.h>

#include <AltSoftSerial.h>
#include <NMEAGPS.h>
#include <GPSport.h>

// Enums and variables
#include "ApplicationStates.h"
#include "ScreenButtons.h"
#include "Pins.h"

// Program module libs
#include "MemoryHandler.h"

#include "ButtonHandler.h"
#include "ScreenManager.h"
#include "MemoryHandler.h"


// Screens and modules
#include "MainMenu.h"



NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

ButtonHandler buttonHandler;
ScreenController screenController;
MemoryController memoryController;

// Menu and subsystems:
MainMenu mainMenu;

const uint8_t screenCharacterCount = 20;
const uint8_t screenLineCount = 4;



// the setup function runs once when you press reset or power the board
void setup() {

	// Initialize the DEBUG serial link:
	Serial.begin(9600);

	Serial.println();
	Serial.println("--- Application starting ---");

	// Initialize the GPS comm
	gpsPort.begin(9600);

	// Starting I2C bus
	Wire.begin();

	// Initialize the connection to the flash memory:
	memoryController.Init();
	AddNewScreenMessages();

	// Create and init the screen:
	screenController.Init(&memoryController, screenCharacterCount, screenLineCount);


	// Set up all the screens and modules:
	mainMenu.Init(&buttonHandler, &screenController);

	/*
	// Setup and enable the GPS and screen power
	pinMode(Pin_GPS_EnablePower, OUTPUT);
	pinMode(Pin_Screen_EnablePower, OUTPUT);

	digitalWrite(Pin_GPS_EnablePower, LOW);
	digitalWrite(Pin_Screen_EnablePower, LOW);


	// Initalize the button handler - it requires working I2C bus
	pButtonHandler.Init();

	if (pButtonHandler.IsDeviceWorking() == false)
	{
		screenController.DisplayText(ScreenMessage_Error_IOChipError, 0, 1);
		
		while (1)
			delay(100000);
	}

	Serial.println("--- Setup completed succesfully ---");

	
	screenController.DisplayText(ScreenMessage_System_NumberTest, 0, 0);
	*/



	/*
	char* data = memoryController.GetScreenMessage(ScreenMessage_System_NumberTest);

	int i;

	Serial.print("Data: ");
	for (i = 0; i < 21; i++)
	{
		Serial.print(data[i], HEX);
		Serial.print(' ');
		delay(50);
	}

	Serial.println();

	Serial.println("Done.");



	screenController.DisplayText(data, 0, 1);
	//screenController.DisplayText(handCraftedData, 0, 1);

	delay(100000);
	*/


	//screenController.DisplayText("Another line", 0, 2);

	/*
	Serial.print("Read data at address JustSail first char: ");
	Serial.println(memoryController.ReadByte(ScreenMessage_Menu_JustSail));

	Serial.print("Read data at address RaceMain first char: ");
	Serial.println(memoryController.ReadByte(ScreenMessage_Menu_RaceMain));
	*/

	/*
	lcd.setCursor(1, 0);
	lcd.print("Doing btn testing.");
	*/
}


int runCounter = 0;
void loop() {

	static unsigned long loopStartTime = millis();
	
	static ApplicationStates currentAppState = AppStates_MainScreen;
	static ApplicationStates newAppState = AppStates_None;
	static bool movingToNewModule = true;


	// First, update the button's status.
	buttonHandler.UpdateButtonStatus();



	// Check if we need to switch to a new screen / module
	// If we do, we need to Init that new screen.
	if (movingToNewModule)
	{
		SwitchToNewState(newAppState);

		// State change handled - remove the flag.
		movingToNewModule = false;
	}
	

	




	//WriteGPSDebugInfo();

	/*
	// Get and refresh the button's status:
	pButtonHandler->UpdateButtonStatus(millis());



	ButtonStatus status = pButtonHandler->GetButtonState(ScreenButton_Confirm);

	switch (status)
	{
		case ScreenButtonStatus_JustPressed:
			Serial.println("Confirm button just pressed!");
			break;
		case ScreenButtonStatus_Pressed:
			Serial.println("Confirm button being held down!");
			break;
		case ScreenButtonStatus_Clicked:
			Serial.println("Confirm button was released!");

		default:
			break;
	}

	delay(150);
	//Serial.println("End");
	*/



	// We need to wait to make sure the button presses are read correctly.
	// As it is isn't a real-time app where timing is oh-so-important
	// we can just wait a little to make sure everything is OK.
	delay(ScreenButtonHandler::minimumMillisecForButtonPress);


	delay(2500);
}

bool RunCurrentModule(ApplicationStates currentAppState, ApplicationStates* newAppState)
{
	switch (currentAppState)
	{
		case AppStates_MainScreen:
			return mainMenu.MainLoop(newAppState);
		case AppStates_JustSailMain:
			break;
		case AppStates_JustSailLaps:
			break;
		case AppStates_RaceSetup:
			break;
		case AppSates_RacePreRace:
			break;
		case AppStates_RaceMain:
			break;
		case AppStates_BouyManager:
			break;
		case AppStates_Statistics:
			break;
		case AppStates_GPSData:
			break;
		case AppStates_DeviceSleep:
			break;
		default:
			return false;
	}

	return false;
}

void SwitchToNewState(ApplicationStates stateToSwitch)
{
	switch (stateToSwitch)
	{
		case AppStates_MainScreen:
			mainMenu.TakeOver();
			break;
		case AppStates_JustSailMain:
			break;
		case AppStates_JustSailLaps:
			break;
		case AppStates_RaceSetup:
			break;
		case AppSates_RacePreRace:
			break;
		case AppStates_RaceMain:
			break;
		case AppStates_BouyManager:
			break;
		case AppStates_Statistics:
			break;
		case AppStates_GPSData:
			break;
		case AppStates_DeviceSleep:
			break;
		default:
			break;
	}
}

void WriteGPSDebugInfo()
{
	/*
	while (gps.available(gpsPort)) {
		fix = gps.read();

		uint8_t satCount = fix.satellites;

		lcd.setCursor(0, 0);
		lcd.print("Sats: ");
		lcd.print(satCount);
		lcd.print(" Vel: ");
		lcd.print(fix.speed_mph(), 1);

		NeoGPS::time_t currentTime = fix.dateTime;

		lcd.setCursor(0, 1);
		lcd.printf("%4d-%02d-%02d %02d:%02d:%02d", currentTime.full_year(), currentTime.month, currentTime.date, currentTime.hours, currentTime.minutes, currentTime.seconds);

		lcd.setCursor(0, 2);
		lcd.print("Lat: ");
		lcd.print(fix.latitude(), 7);

		lcd.setCursor(0, 3);
		lcd.print("Lon: ");
		lcd.print(fix.longitude(), 7);
	}
	*/
}



void AddNewScreenMessages()
{

	memoryController.EraseWholeMemory(true, true, true);

	// ---------------------------------------------------------
	// DO NOT FORGET TO UPDATE THE MemoryHandler.ccp file's GetMemoryAddressForScreenMessage METHOD IF YOU UPDATE THESE!!!!!!
	// ---------------------------------------------------------
	
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_System_SystemReady,		"   System Ready!    ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_System_AppName,			"SailingSpeed-O-Meter");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_System_LoadingCentered, "      Loading...    ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_System_NumberTest,		"01234567890123456789");


	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_JustSail,			"  Just sail         ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_RaceMain,			"  Race!             ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_BouySystem,		"  Bouy system       ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_Statistics,		"  Statistics        ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_GPSDataMain,		"  GPS data          ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_DeviceSleep,		"  Device sleep      ");

	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Spec_SelectorLeft,		">                   ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Spec_SelectorDown,		"V                   ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Spec_SelectorRight,		"<                   ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Spec_SelectorUp,		"^                   ");


	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Error_IOChipError,		"   IO Chip error!   ");

	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Error_UnsupportedSCRADD,"Unsupported SCR ADD ");

	// ---------------------------------------------------------
	// DO NOT FORGET TO UPDATE THE MemoryHandler.ccp file's GetMemoryAddressForScreenMessage METHOD IF YOU UPDATE THESE!!!!!!
	// ---------------------------------------------------------
}


