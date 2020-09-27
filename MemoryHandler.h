// MemoryHandler.h

#ifndef _MEMORYHANDLER_h
#define _MEMORYHANDLER_h

#include "arduino.h"

#include "ScreenMessages.h"
#include <SPIMemory.h>

/*

Main memory unit controller

How the used flash memory is built:

Each sector is 4kbyte, which is organized into the following blocks:

- Parameter sectors:
  used for screen messages. Each message take EXACTLY 20 bytes.
  (Please see the ScreenMessages.h for fix addresses)
1. 8kbyte
	- Informations
	- Address range: 0 - 8191
2. 8kbyte
    - Menu texts
	- Address range: 8192 - 16383
3. 8kbyte
	- Special, function texts / characters
	- Address range: 16384 - 24575
4. 8kbyte
    - Errors / Alerts
	- Address range: 24576 - 32767


- Overlay:
5. 32 kbyte
   -
   - Address range: 32768 - 65536 (per byte)

- Main data:
6 - 67. 64 kbyte

- Overlay:
68. 32 kbyte

- Parameter sectors:
69. 8kbyte
70. 8kbyte
71. 8kbyte
72. 8kbyte

---------------------------------------------------

Program layout:

Each main sector will have one, pre-dedicated task to ensure sufficiant space.

*/

namespace MemoryHandler
{
	class MemoryController
	{
		public:

			void Init();

			char* GetScreenMessage(ScreenMessage messageAddress);
			byte ReadByte(uint32_t address);

			uint32_t GetMemoryAddressForScreenMessage(ScreenMessage message);

			void StorePreSetScreenMessagesIfNotYetSet(ScreenMessage address, char data[20]);

			void EraseWholeMemory(bool confirm, bool secondConfirm, bool thirdConfim);
			
		private:

			SPIFlash flash;
			char buffer[21];
	};
}

using namespace MemoryHandler;

#endif

