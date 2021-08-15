#include <MemoryHexDump.h>



void setup() {
	while (!Serial && millis() < 5000) ;
	Serial.begin(115200);

	Serial.println("DTCM");
	Serial.println("*** Duplicates not removed ***");
	MemoryHexDump(Serial, (void*)0x020000000, 1024, false);
	Serial.println("*** Duplicates removed ***");
	MemoryHexDump(Serial, (void*)0x020000000, 1024, true);

	Serial.println("\n\nOCRAM2");
	Serial.println("*** Duplicates not removed ***");
	MemoryHexDump(Serial, (void*)0x020200000, 1024, false);
	Serial.println("*** Duplicates removed ***");
	MemoryHexDump(Serial, (void*)0x020200000, 1024, true);

}

void loop() {

}