#pragma once

enum ButtonStatus :byte
{

	ScreenButtonStatus_None = 0x00,

	// The button pressed just now, it was unpressed previously.
	ScreenButtonStatus_JustPressed = 0x01,

	// The button was either pressed or unpressed last time
	// but it is pressed now (user holding it down).
	ScreenButtonStatus_Pressed = 0x02,

	// The button was pressed, but it is released now.
	ScreenButtonStatus_Clicked = 0x03,
};
