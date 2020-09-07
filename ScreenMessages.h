#pragma once



enum ScreenMessage : uint32_t
{
	// ------------------------- System informations -------------------------

	// First parameter section
	// Address range: 0 - 8191

	// "   System Ready!    "
	ScreenMessage_System_SystemReady = 0,

	// ---------------------------- Menu messages: ---------------------------

	// Second parameter section
	// Address range: 8192 - 16383

	// " Just sail          "
	ScreenMessage_Menu_JustSail = 8192,

	// " Race!              "
	ScreenMessage_Menu_RaceMain = 8212,

	// " Bouy system        "
	ScreenMessage_Menu_BouySystem = 8232,

	// " Statistics         "
	ScreenMessage_Menu_Statistics = 8252,

	// " GPS data           "
	ScreenMessage_Menu_GPSDataMain = 8272,

	// " Device sleep       "
	ScreenMessage_Menu_DeviceSleep = 8292,


	// ----------------------------  Error messages: -------------------------

	// "   IO Chip error!   "
	ScreenMessage_Error_IOChipError = 24576,
};