#include <Arduino.h>

/* we can place arbitrary objects into that flash section we've rserved. 
 * e.g., multiple constant things. 
 * or nothing at all (and it would still be reserved).
 * here, we just place a constant buffer in flash that occupies the entire sector.
 * note that size checking exists. Add one to the sector size and it will fail to compile.
*/
#define SECTOR_SIZE (16*1024)
const uint8_t reserved_flash_sector[SECTOR_SIZE] __attribute__((__used__))  __attribute__ ((section (".reserved_flash"))) = {(uint8_t)'T', (uint8_t)'E', (uint8_t)'S', (uint8_t)'T', 0x00};
extern "C" uint32_t _reserved_flash_start; /* provided by ld script: we can see the starte and end address of the reserved / used flash page */
extern "C" uint32_t _reserved_flash_end; /* provided by ld script: we can see the starte and end address of the reserved / used flash page */

void setup() {
  SerialUSB.begin(115200);
  SerialUSB.println("Hello world!");
  pinMode(PC13, OUTPUT);
}

void loop() {
  SerialUSB.println("Address of reversed flash sector buffer object: 0x" + String((uint32_t)&reserved_flash_sector, HEX));
  SerialUSB.println("Length of reversed flash sector buffer object: " + String(sizeof(reserved_flash_sector)));
  SerialUSB.println("_reserved_flash_start: 0x" + String((uint32_t)&_reserved_flash_start, HEX));
  SerialUSB.println("_reserved_flash_start: 0x" + String((uint32_t)&_reserved_flash_end, HEX));
  digitalWrite(PC13, HIGH);
  delay(1000);
  digitalWrite(PC13, LOW);
  delay(1000);
}