# PlatformIO Example for STM32 Firmware with Reserved Flash Sector

See https://community.platformio.org/t/how-to-reserve-a-page-of-flash-memory-stm32-arduino/18664.

This firmware restructures the linker script in such a way that the first flash sector (16 kByte) is only used for the ISR vector (which is around 400 bytes big), then leaves the next 16KByte reserved, and then places all code (`.text`) and read-only constants and everything.

Normal (*constant*) C/C++ objects can also be placed in flash with the `__attribute__ ((section (".reserved_flash")))` attribute.

Note that to write anything, you must not dereference a pointer to the memory address, but use the `HAL_FLASH_x` functions (`HAL_FLASHEx_Erase`, `HAL_FLASH_Program`) for erasing and programming the sector. 

Reading can be done with a normal pointer though.

The code tests the validity of the reserved flash by placing a buffer object in the allocated section of maximum size, then printing the address of it, as long with linker-provided symbols for the start and end of the sector.
