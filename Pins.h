#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// ---- Screen pins ----

// Set LOW to enable, HIGH to disable
const uint8_t Pin_Screen_EnablePower = 5;

const uint8_t Pin_Screen_RS = A3;
const uint8_t Pin_Screen_EN = A2;
const uint8_t Pin_Screen_D4 = A1;
const uint8_t Pin_Screen_D5 = A0;
const uint8_t Pin_Screen_D6 = 6;
const uint8_t Pin_Screen_D7 = 7;

// ---- GPS pins ----

// Set LOW to enable, HIGH to disable
const uint8_t Pin_GPS_EnablePower = 4;
