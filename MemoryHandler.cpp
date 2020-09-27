// 
// 
// 

#include "MemoryHandler.h"


void MemoryController::Init()
{
	// Start the connection to the flash memory:
	flash.setClock(1000000); // 1Mhz just to be safe.
	flash.begin();

	byte i;
	for (i = 0; i < 21; i++)
	{
		buffer[i] = '\0';
	}
}

char* MemoryController::GetScreenMessage(ScreenMessage messageAddress)
{
	uint32_t physicalAddress = GetMemoryAddressForScreenMessage(messageAddress);

	if (physicalAddress == 0)
	{
		// If the address is 0 that means the data we asked for doesn't exists
		// (at least the developer forgot to enter it...)
		physicalAddress = GetMemoryAddressForScreenMessage(ScreenMessage_Error_UnsupportedSCRADD);
		flash.readCharArray(physicalAddress, buffer, 20);
	}
	else
		flash.readCharArray(physicalAddress, buffer, 20);


	return buffer;
}

byte MemoryController::ReadByte(uint32_t address)
{
	return flash.readByte(address);
}

void MemoryController::StorePreSetScreenMessagesIfNotYetSet(ScreenMessage address, char data[20])
{
	// If the given address is empty
	// then every bit will be set to 1 (255 for a byte)
	// If any data was written there, then (hopefully) we didn't wrote a 255.

	uint32_t physicalAddress = GetMemoryAddressForScreenMessage(address);

	byte dataOnFirstByte = ReadByte(physicalAddress);

	if(dataOnFirstByte == 255)
		flash.writeCharArray(physicalAddress, data, 20, true);
	else
	{
		Serial.println("Error. Address already filled.");
	}
}

void MemoryController::EraseWholeMemory(bool confirm, bool secondConfirm, bool thirdConfim)
{
	if (confirm && secondConfirm && thirdConfim)
		flash.eraseChip();
}

uint32_t MemoryController::GetMemoryAddressForScreenMessage(ScreenMessage message)
{
	// Please note: Flash address 0 NOT USED!
	// We use it as a "Not found" return code
	// which has a different meaning for each data type.

	switch (message)
	{
		case ScreenMessage_System_SystemReady:
			return 1;
		case ScreenMessage_System_AppName:
			return 21;
		case ScreenMessage_System_LoadingCentered:
			return 41;
		case ScreenMessage_System_NumberTest:
			return 61;

		case ScreenMessage_Menu_JustSail:
			return 8192;
		case ScreenMessage_Menu_RaceMain:
			return 8212;
		case ScreenMessage_Menu_BouySystem:
			return 8232;
		case ScreenMessage_Menu_Statistics:
			return 8252;
		case ScreenMessage_Menu_GPSDataMain:
			return 8272;
		case ScreenMessage_Menu_DeviceSleep:
			return 8292;

		case ScreenMessage_Spec_SelectorLeft:
			return 16384;
		case ScreenMessage_Spec_SelectorDown:
			return 16404;
		case ScreenMessage_Spec_SelectorRight:
			return 16424;
		case ScreenMessage_Spec_SelectorUp:
			return 16444;

		case ScreenMessage_Error_IOChipError:
			return 24576;
		case ScreenMessage_Error_UnsupportedSCRADD:
			return 24596;

		default:
			return 0;
	}
}

