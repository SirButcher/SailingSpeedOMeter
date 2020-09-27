#pragma once

#include "arduino.h"

enum ScreenMessage
{
	// ------------------------- System informations -------------------------

	// First parameter section
	// Address range: 0 - 8191

	// "   System Ready!    "
	ScreenMessage_System_SystemReady,

	// "SailingSpeed-O-Meter"
	ScreenMessage_System_AppName,

	// "      Loading...    "
	ScreenMessage_System_LoadingCentered,

	// "01234567890123456789"
	ScreenMessage_System_NumberTest,

	// ---------------------------- Menu messages: ---------------------------

	// Second parameter section
	// Address range: 8192 - 16383

	// "  Just sail         "
	ScreenMessage_Menu_JustSail,

	// "  Race!             "
	ScreenMessage_Menu_RaceMain,

	// "  Bouy system       "
	ScreenMessage_Menu_BouySystem,

	// "  Statistics        "
	ScreenMessage_Menu_Statistics,

	// "  GPS data          "
	ScreenMessage_Menu_GPSDataMain,

	// "  Device sleep      "
	ScreenMessage_Menu_DeviceSleep,

	// ------------------------ Special, function keys -----------------------

	// ">                   "
	ScreenMessage_Spec_HorSelector,

	// "V                   "
	ScreenMessage_Spec_VerSelector,


	// ----------------------------  Error messages: -------------------------

	// "   IO Chip error!   "
	ScreenMessage_Error_IOChipError,

	// "Unsupported SCR ADD "
	ScreenMessage_Error_UnsupportedSCRADD,
};