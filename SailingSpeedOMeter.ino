/*
 Name:		SailingSpeedOMeter.ino
 Created:	25/06/2020 02:17:23 PM
 Author:	Gabriel Butcher
*/


#include "Pins.h"

#include <Wire.h>
#include <LiquidCrystal.h> 

#include <AltSoftSerial.h>
#include <NMEAGPS.h>
#include <GPSport.h>

#include <SPIMemory.h>

#include "ButtonHandler.h"



const long msInDay = 86400000; // 86400000 milliseconds in a day
const long msInHour = 3600000; // 3600000 milliseconds in an hour
const long msInMinute = 60000; // 60000 milliseconds in a minute
const long msInSecond = 1000; // 1000 milliseconds in a second


uint32_t StartTime;
bool recordElapsedTime = false;
uint32_t lastSaveTimeStamp = 0;
const uint32_t msPerSave = 10 * msInMinute * msInSecond;

SPIFlash flash;
uint32_t freeFlashAddress;

LiquidCrystal lcd(Pin_Screen_RS, Pin_Screen_EN, Pin_Screen_D4, Pin_Screen_D5, Pin_Screen_D6, Pin_Screen_D7);


char convertedTime[17] = "00d 00:00:00.000";
byte RTCTimeBuffer[7] = { 0, 0, 0, 0, 0, 0, 0 };

int loopCounter = 0;
bool firstSuccess = false;

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


	buttonHandler = new ButtonHandler();

	if (buttonHandler->IsDeviceWorking() == false)
	{
		Serial.println("IO extender ran into a problem!");
	}


	Serial.println("--- Setup completed succesfully ---");

	StartTime = millis();

	lcd.setCursor(1, 0);
	lcd.print("Doing btn testing.");
}

// the loop function runs over and over again until power down or reset
void loop() {

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
	/*
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
	*/
}

void MeasureElapsedTime()
{
	uint32_t currentTime = millis();
	uint32_t elapsedTime = currentTime - StartTime;

	ConvertMillisIntoTime(elapsedTime, convertedTime);

	lcd.setCursor(0, 1);         // move cursor to   (2, 1)
	lcd.print(convertedTime);      // print message at (2, 1)


	if (recordElapsedTime == false)
	{
		// read the state of the pushbutton value:
		int buttonState = digitalRead(5);

		// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
		if (buttonState == HIGH)
		{
			recordElapsedTime = true;
			//Serial.println("Save enabled!");
		}
	}

	if (recordElapsedTime && (currentTime - lastSaveTimeStamp) > msPerSave)
	{
		freeFlashAddress = flash.getAddress(sizeof(uint32_t));

		bool saveSuccess = flash.writeULong(freeFlashAddress, elapsedTime, true);
		lastSaveTimeStamp = currentTime;

		//Serial.print("Save status: ");
		//Serial.println(saveSuccess);

		if (saveSuccess == false)
		{
			lcd.setCursor(0, 3);
			lcd.print("Save failed!!");
		}
	}
}

void ConvertMillisIntoTime(unsigned long elapsedTime, char array[])
{
	// The format is the following:
	// 00d 00:00:00.000

	int days = elapsedTime / msInDay;
	int hours = (elapsedTime % msInDay) / msInHour;
	int minutes = ((elapsedTime % msInDay) % msInHour) / msInMinute;
	int seconds = (((elapsedTime % msInDay) % msInHour) % msInMinute) / msInSecond;
	int milliseconds = elapsedTime - (days * msInDay) - (hours * msInHour) - (minutes * msInMinute) - (seconds * msInSecond);

	AddNumberToArray(days, 2, 0, array);
	AddNumberToArray(hours, 2, 4, array);
	AddNumberToArray(minutes, 2, 7, array);
	AddNumberToArray(seconds, 2, 10, array);
	AddNumberToArray(milliseconds, 3, 13, array);
}

void AddNumberToArray(int number, int lenght, int startPos, char array[17])
{
	int i;
	int c = 0;

	char converted[5]; // Max lenght is 3 character

	itoa(number, converted, 10);

	int numberLenght = GetLenght(number);

	for (i = 0; i < lenght; i++)
	{
		if(i < (lenght - numberLenght))
			array[startPos + i] = '0';
		else
			array[startPos + i] = converted[c++];
	}
}
int GetLenght(int number)
{
	if (number < 10)
		return 1;
	else if (number < 100)
		return 2;
	else if (number < 1000)
		return 3;
}


void I2CScanner() {
	int nDevices = 0;

	Serial.println("Scanning...");

	for (byte address = 1; address < 127; ++address) {
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		byte error = Wire.endTransmission();

		if (error == 0) {
			Serial.print("I2C device found at address 0x");
			if (address < 16) {
				Serial.print("0");
			}
			Serial.print(address, HEX);
			Serial.println("  !");

			++nDevices;
		}
		else if (error == 4) {
			Serial.print("Unknown error at address 0x");
			if (address < 16) {
				Serial.print("0");
			}
			Serial.println(address, HEX);
		}
	}
	if (nDevices == 0) {
		Serial.println("No I2C devices found\n");
	}
	else {
		Serial.println("done\n");
	}
	delay(5000); // Wait 5 seconds for next scan
}
