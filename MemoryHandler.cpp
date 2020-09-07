// 
// 
// 

#include "MemoryHandler.h"

void MemoryHandler::MemoryController::Init()
{
	// Start the connection to the flash memory:
	flash.setClock(1000000); // 1Mhz just to be safe.
	flash.begin();

	//StorePreSetScreenMessages();
}

char* MemoryHandler::MemoryController::GetScreenMessage(ScreenMessage message)
{
	flash.readCharArray(message, buffer, 20, false);

	return buffer;
}

byte MemoryHandler::MemoryController::ReadByte(uint32_t address)
{
	return flash.readByte(address);
}

void MemoryHandler::MemoryController::StorePreSetScreenMessagesIfNotYetSet(ScreenMessage address, char data[20])
{
	// If the given address is empty
	// then every bit will be set to 1 (255 for a byte)
	// If any data was written there, then (hopefully) we didn't wrote a 255.

	flash.writeCharArray(address, data, 20, true);

	/*
	byte dataOnFirstByte = ReadByte(address);

	if(dataOnFirstByte != 255)
		flash.writeCharArray(address, data, 20, true);
	*/
}

void MemoryHandler::MemoryController::EraseWholeMemory(bool confirm, bool secondConfirm, bool thirdConfim)
{
	if (confirm && secondConfirm && thirdConfim)
		flash.eraseChip();
}


