#pragma once

#include "arduino.h"

enum ScreenButton :byte
{
	// Button IO0
	ScreenButton_Confirm = 0x01,
	// Button IO1
	ScreenButton_Cancel = 0x00,
	// Button IO2
	ScreenButton_Up = 0x03,
	// Button IO3
	ScreenButton_Down = 0x02,
};
