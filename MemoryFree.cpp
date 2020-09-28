// From:
// https://github.com/mpflaga/Arduino-MemoryFree

#include "MemoryFree.h"

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char* __brkval;
#endif  // __arm__

int MemoryFree::MemoryStatus::freeMemory()
{
	char top;
#ifdef __arm__
	return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
	return &top - __brkval;
#else  // __arm__
	return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

void MemoryFree::MemoryStatus::WriteFreeMemoryToSerial()
{
	Serial.print(F("Free RAM: "));
	Serial.println(freeMemory(), DEC);
}

void MemoryFree::MemoryStatus::CheckMemoryStatusAt(const __FlashStringHelper* textToDisplay)
{
	static int lastMemoryStatus = 0;

	if (lastMemoryStatus != freeMemory())
	{
		Serial.print(F("Memory at "));
		Serial.print(textToDisplay);
		Serial.print(F(" is: "));
		Serial.print(freeMemory());
		Serial.println(F(" bytes"));

		lastMemoryStatus = freeMemory();
	}
}

void MemoryFree::MemoryStatus::CheckMemoryStatusAt(const __FlashStringHelper* textToDisplay, int numberToAddAfterText)
{
	static int lastMemoryStatus = 0;

	if (lastMemoryStatus != freeMemory())
	{
		Serial.print(F("Memory at "));
		Serial.print(textToDisplay);
		Serial.print(numberToAddAfterText);
		Serial.print(F(" is: "));
		Serial.print(freeMemory());
		Serial.println(F(" bytes"));

		lastMemoryStatus = freeMemory();
	}
}
