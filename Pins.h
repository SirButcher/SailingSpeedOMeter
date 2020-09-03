#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// ---- Screen pins ----

// Set LOW to enable, HIGH to disable
const int Pin_Screen_EnablePower = 5;

const int Pin_Screen_RS = A3;
const int Pin_Screen_EN = A2;
const int Pin_Screen_D4 = A1;
const int Pin_Screen_D5 = A0;
const int Pin_Screen_D6 = 6;
const int Pin_Screen_D7 = 7;

// ---- GPS pins ----

// Set LOW to enable, HIGH to disable
const int Pin_GPS_EnablePower = 4;
