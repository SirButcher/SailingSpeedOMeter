/*
 Name:		SailingSpeedOMeter.ino
 Created:	25/06/2020 02:17:23 PM
 Author:	Gabriel Butcher
*/

#include "Pins.h"
#include "Enums.h"

#include <Wire.h>
#include <LiquidCrystal.h> 

#include <AltSoftSerial.h>
#include <NMEAGPS.h>
#include <GPSport.h>

#include <SPIMemory.h>

#include "ButtonHandler.h"


SPIFlash flash;
uint32_t freeFlashAddress;

ApplicationStates currentAppState = AppStates_MainScreen;

LiquidCrystal lcd(Pin_Screen_RS, Pin_Screen_EN, Pin_Screen_D4, Pin_Screen_D5, Pin_Screen_D6, Pin_Screen_D7);

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values
ButtonHandler* buttonHandler;


// the setup function runs once when you press reset or power the board
void setup() {

	// Initialize the DEBUG serial link:
	Serial.begin(9600);

	Serial.println();
	Serial.println("--- Application starting ---");

	// Initialize the GPS comm
	gpsPort.begin(9600);

	// Start the connection to the flash memory:
	flash.setClock(1000000); // 1Mhz just to be safe.
	flash.begin();

	// Setup and enable the GPS and screen power
	pinMode(Pin_GPS_EnablePower, OUTPUT);
	pinMode(Pin_Screen_EnablePower, OUTPUT);

	digitalWrite(Pin_GPS_EnablePower, LOW);
	digitalWrite(Pin_Screen_EnablePower, LOW);

	// Starting I2C bus...
	Wire.begin();

	// Initialize the screen's starting params
	lcd.begin(20, 4); // set up number of columns and rows
	lcd.clear();
	lcd.display();

	// Initalize the button handler - it requires working I2C bus
	buttonHandler = new ButtonHandler();

	if (buttonHandler->IsDeviceWorking() == false)
	{
		Serial.println("IO extender ran into a problem!");
	}

	Serial.println("--- Setup completed succesfully ---");

	lcd.setCursor(1, 0);
	lcd.print("Doing btn testing.");
}

// the loop function runs over and over again until power down or reset
void loop() {

	// Get and refresh the button's status:
	buttonHandler->UpdateButtonStatus(millis());



	ButtonStatus status = buttonHandler->GetButtonState(ScreenButton_Confirm);

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
}

void WriteGPSDebugInfo()
{

	//lcd.clear();
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
}