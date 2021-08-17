#include <MemoryHexDump.h>


uint8_t buffer[256] = "Start of buffer";


void setup() {
	while (!Serial && millis() < 5000) ;
	Serial.begin(115200);

	buffer[248] = 'E';
	buffer[249] = 'n';
	buffer[250] = 'd';
	buffer[252] = '!';
	buffer[253] = '!';
	buffer[254] = '.';
	MemoryHexDump(Serial, buffer, sizeof(buffer), false, "\n*** Buffer  dups not removed ***\n");
	MemoryHexDump(Serial, buffer, sizeof(buffer), true, "\n*** Buffer dups removed ***\n");
	
	MemoryHexDump(Serial, (void*)0x020000000, 1024, false, "\n*** DTCM Duplicates not removed ***\n");
	MemoryHexDump(Serial, (void*)0x020000000, 1024, true, "\n*** DTCM Duplicates removed ***\n");

	Serial.println("\n\nOCRAM2");
	Serial.println("*** Duplicates not removed ***");
	MemoryHexDump(Serial, (void*)0x020200000, 1024, false);
	Serial.println("*** Duplicates removed ***");
	MemoryHexDump(Serial, (void*)0x020200000, 1024, true);

}

void loop() {

}