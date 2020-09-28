// From:
// https://github.com/mpflaga/Arduino-MemoryFree

// memoryFree header
// From http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720/15
// ...written by user "mem".

#pragma once

#ifndef	MEMORYFREE_H
#define MEMORYFREE_H

#include <Arduino.h>

namespace MemoryFree {

	class MemoryStatus {

	public:

		static void WriteFreeMemoryToSerial();

		static void CheckMemoryStatusAt(const __FlashStringHelper* textToDisplay);

		static void CheckMemoryStatusAt(const __FlashStringHelper* textToDisplay, int numberToAddAfterText);

	private:

		static int freeMemory();
	};
}



#endif