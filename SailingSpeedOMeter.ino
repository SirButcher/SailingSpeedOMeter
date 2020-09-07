/*
 Name:		SailingSpeedOMeter.ino
 Created:	25/06/2020 02:17:23 PM
 Author:	Gabriel Butcher
*/


#include "MemoryHandler.h"
#include "Pins.h"
#include "Enums.h"

#include <stdarg.h>

#include <Wire.h>


#include <AltSoftSerial.h>
#include <NMEAGPS.h>
#include <GPSport.h>

#include "ButtonHandler.h"
#include "ScreenManager.h"
#include "MemoryHandler.h"




ApplicationStates currentAppState = AppStates_MainScreen;

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

ButtonHandler pButtonHandler;
ScreenController screenController;
MemoryController memoryController;

const int screenCharacterCount = 20;
const int screenLineCount = 4;


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


int textToDisplay = 0;
// the loop function runs over and over again until power down or reset
void loop() {

	pButtonHandler.UpdateButtonStatus(millis());

	// We need to wait to make sure the 
	// button pressed will be read correctly.
	delay(5); 


	bool textChanged = false;


	if (pButtonHandler.GetButtonState(ScreenButton_Down) == ScreenButtonStatus_JustPressed)
	{
		textChanged = true;
		textToDisplay++;

	}
	else if (pButtonHandler.GetButtonState(ScreenButton_Up) == ScreenButtonStatus_JustPressed)
	{
		textToDisplay--;
		textChanged = true;
	}
	else if (pButtonHandler.GetButtonState(ScreenButton_Confirm) == ScreenButtonStatus_JustPressed)
	{
		screenController.ClearWholeScreen();
	}
	else if (pButtonHandler.GetButtonState(ScreenButton_Cancel) == ScreenButtonStatus_JustPressed)
	{
	}

	if (textToDisplay > 7)
		textToDisplay = 0;
	if (textToDisplay < 0)
		textToDisplay = 7;

	if (!textChanged)
		return;

	switch (textToDisplay)
	{
		case 0:
			screenController.DisplayText(ScreenMessage_System_SystemReady, 0, 1);
			break;
		case 1:
			screenController.DisplayText(ScreenMessage_Menu_JustSail, 0, 1);
			break;
		case 2:
			screenController.DisplayText(ScreenMessage_Menu_RaceMain, 0, 1);
			break;
		case 3:
			screenController.DisplayText(ScreenMessage_Menu_BouySystem, 0, 1);
			break;
		case 4:
			screenController.DisplayText(ScreenMessage_Menu_Statistics, 0, 1);
			break;
		case 5:
			screenController.DisplayText(ScreenMessage_Menu_GPSDataMain, 0, 1);
			break;
		case 6:
			screenController.DisplayText(ScreenMessage_Menu_DeviceSleep, 0, 1);
			break;
		case 7:
			screenController.DisplayText(ScreenMessage_Error_IOChipError, 0, 1);
			break;

		default:
			break;
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

	/*
	memoryController.EraseWholeMemory(true, true, true);

	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_System_SystemReady, "   System Ready!    ");

	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_JustSail, "  Just sail         ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_RaceMain, "  Race!             ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_BouySystem, "  Bouy system       ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_Statistics, "  Statistics        ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_GPSDataMain, "  GPS data          ");
	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Menu_DeviceSleep, "  Device sleep      ");

	memoryController.StorePreSetScreenMessagesIfNotYetSet(ScreenMessage_Error_IOChipError, "   IO Chip error!   ");
	*/

}


