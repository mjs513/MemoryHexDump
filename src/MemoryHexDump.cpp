// https://github.com/kurte/MemoryDump
//
// Warning this is Kurt's hacked up Memory dump library
//    probably like 50 other dump libraries...
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED
#include "MemoryHexDump.h"


static void output_one_line(Print& out, uint8_t const* mem, size_t count) {
	const uint8_t *p = mem;
	out.print((uint32_t)p < 0x10000 ? "0000" : (uint32_t)p < 0x100000 ? "000" : (uint32_t)p < 0x1000000 ? "00" : (uint32_t)p < 0x1000000 ? "0" : "");
	out.print((uint32_t)p < 0x10 ? "000" : (uint32_t)p < 0x100 ? "00" : (uint32_t)p < 0x1000 ? "0" : "");
	out.print((uint32_t)p, HEX);
	out.print(" - ");

	// Now output the hex values
	for (uint32_t c = 0; c < 16; c++) {
		// Because ISO C forbids `void*` arithmetic, we have to do some funky casting
		if (c < count) {
			uint8_t ch = *p++;
			if (ch < 16) out.print("0");
			out.print(ch, HEX);
			out.write(' ');
		} else {
			out.print("   "); // alignment characters
		}
		if (c == 7) out.write(' ');
	}
	// Now lets output the Ascii values for these.
	out.print(" : ");
	p = mem;
	for (int c = 0; c < 16 && count; c++) {
		// Because ISO C forbids `void*` arithmetic, we have to do some funky casting
		uint8_t ch = *p++;
		count--;
		out.write(((ch > 0x1f) && (ch < 0x7f)) ? ch : '.');
		if (c == 7) out.write(' ');
	}
	out.println();
}

void MemoryHexDump(Print& out, void const* mem, size_t count, bool remove_duplicate_lines, const char *szTitle )
{
	const uint8_t *p;
	const uint8_t *last_line_output = nullptr;
	if ( NULL != szTitle ) out.print( szTitle );
	if ( mem < (uint8_t *)32 ) {
		out.print(" Given addr of ");
		out.print( (uint32_t)mem );
		out.print("  *Skipping Addresses < 32 to avoid access violation\n");
		mem = (void const*)32;
		p = (const uint8_t *)mem;
	}
	else
		p = (const uint8_t *)mem;
	uint32_t output_count = 16;
	uint32_t duplicate_line_cached = 0;
	while (count > 0) {
		if (remove_duplicate_lines && last_line_output) {
			if ((count < 16) || (memcmp(last_line_output, p, 16) != 0)) {
				// end of run.
				if (0 != duplicate_line_cached) {
					if ((p - 16) != last_line_output && 1 < duplicate_line_cached) {
						out.print("...\t ");
						out.print(duplicate_line_cached-1);
						out.print(" duplicate line(s) removed.\n");
					}
					output_one_line(out, p - 16, output_count);					
				}
				duplicate_line_cached = 0;
			} else {
				duplicate_line_cached++;
			}
		}
		if (count < output_count) output_count = count;

		if (0 == duplicate_line_cached) {
			output_one_line(out, p, output_count);
			last_line_output = p;
		}
		count -= output_count;
		p += output_count;
	}
	if (0 != duplicate_line_cached) {
		// last line was a duplicate and 16 bytes long
		if ((p - 16) != last_line_output && 1 < duplicate_line_cached) {
			out.print("...\t ");
			out.print(duplicate_line_cached-1);
			out.print(" duplicate line(s) removed.\n");
		}
		output_one_line(out, p - 16, output_count);
	}
}
