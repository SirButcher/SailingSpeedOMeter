// 
// 
// 

#include "MemoryHandler.h"






void MemoryHandler::MemoryController::Init()
{
	// Start the connection to the flash memory:
	flash.setClock(1000000); // 1Mhz just to be safe.
	flash.begin();

	byte i;
	for (i = 0; i < 21; i++)
	{
		buffer[i] = '\0';
	}

	//StorePreSetScreenMessages();
}

char* MemoryHandler::MemoryController::GetScreenMessage(ScreenMessage messageAddress)
{
	flash.readCharArray(messageAddress, buffer, 20);

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

	byte dataOnFirstByte = ReadByte(address);
	Serial.print("Byte: ");
	Serial.println(dataOnFirstByte);

	/*
	

	if(dataOnFirstByte != 255)
		flash.writeCharArray(address, data, 20, true);
	*/

	flash.writeCharArray(address, data, 20, true);
}

void MemoryHandler::MemoryController::EraseWholeMemory(bool confirm, bool secondConfirm, bool thirdConfim)
{
	if (confirm && secondConfirm && thirdConfim)
		flash.eraseChip();
}


