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

void MemoryHandler::MemoryController::StorePreSetScreenMessages()
{
	//flash.writeCharArray(ScreenMessage_System_SystemReady, "   System Ready!   ", 20, true);
	//flash.writeCharArray(ScreenMessage_Error_IOChipError, "   IO Chip error!  ", 20, true);
}

