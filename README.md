# MemoryHexDump

This is a simple library that dumps memory to whichever Arduino Print object you specify. 

This is really nothing special, as there are probably at least 100 similar code bases that dump memory in Hex.

This code shows 16 bytes per line in HEX and then shows the bytes in ASCII if in proper range else a .

Note: this code does not include anything to work in the PROGMEM area of 8 bit AVR processors. 

## API

### RAM

```c++
void MemoryHexDump(Print& out, void const* address, size_t count, bool remove_duplicate_lines, 
	const char *szTitle=NULL, uint32_t max_output_lines=(uint32_t)-1, 
	uint32_t starting_display_addr = (uint32_t)-1 );

```
Dumps memory starting at some address for so many bytes.  It also has an option to 
try to not show duplicate lines. 

- **out** : A reference to any object that is derived from the Print class, such as Serial
- **address** : The memory pointer
- **count** : The count of how many bytes to dump out
- **remove_duplicate_lines**: Should we try to reduce output by not showing several lines that have the same 16 bytes?
- **szTitle** : Optional Title string
- **max_output_lines** : Optional can limit how many lines are output
- **starting_display_addr** : Optional can use different count instead of memory address, used in SDFileDump example


## Output example
Here is showing output with duplicate lines removes:

```
Buffer - Dups not removed
200001E0 - 53 74 61 72 74 20 6F 66  20 42 75 66 66 65 72 00  : Start of  Buffer.
200001F0 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000200 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000210 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000220 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000230 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000240 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000250 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000260 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000270 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000280 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000290 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
200002A0 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
200002B0 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
200002C0 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
200002D0 - 00 00 00 00 00 00 00 00  00 00 45 6E 64 21 21 00  : ........ ..End!!.

Buffer - Dups removed
200001E0 - 53 74 61 72 74 20 6F 66  20 42 75 66 66 65 72 00  : Start of  Buffer.
200001F0 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
...	 12 duplicate line(s) removed.
200002C0 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
200002D0 - 00 00 00 00 00 00 00 00  00 00 45 6E 64 21 21 00  : ........ ..End!!.

```
