// https://github.com/kurte/MemoryHexDump
//
// Warning this is Kurt's hacked up Memory dump library
//    probably like 50 other dump libraries...
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED
#ifndef _memoryhexdump_h_
#define _memoryhexdump_h_

#include <Arduino.h>

void MemoryHexDump(Print& out, void const* address, size_t count, bool remove_duplicate_lines, 
	const char *szTitle=NULL, uint32_t max_output_lines=(uint32_t)-1);

#endif