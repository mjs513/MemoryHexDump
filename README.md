# MemoryHexDump

This is a simple library that dumps memory to whichever Arduino Print object you specify. 

This is really nothing special, as there are probably at least 100 similar code bases that dump memory in Hex.

This code shows 16 bytes per line in HEX and then shows the bytes in ASCII if in proper range else a .

Note: this code does not include anything to work in the PROGMEM area of 8 bit AVR processors. 

## API

### RAM

```c++
void MemoryHexDump(Print& out, void const* address, size_t count, bool remove_duplicate_lines);

```
Dumps memory starting at some address for so many bytes.  It also has an option to 
try to not show duplicate lines. 

- **out** : A reference to any object that is derived from the Print class, such as Serial
- **address** : The memory pointer
- **count** : The count of how many bytes to dump out
- **remove_duplicate_lines**: Should we try to reduce output by not showing several lines that have the same 16 bytes?

## Output example
Here is showing output with duplicate lines removes:

```
*** Duplicates removed ***
20000000 - 44 54 43 4D 00 00 00 00  2A 2A 2A 20 44 75 70 6C  : DTCM.... *** Dupl
20000010 - 69 63 61 74 65 73 20 6E  6F 74 20 72 65 6D 6F 76  : icates n ot remov
20000020 - 65 64 20 2A 2A 2A 00 00  2A 2A 2A 20 44 75 70 6C  : ed ***.. *** Dupl
20000030 - 69 63 61 74 65 73 20 72  65 6D 6F 76 65 64 20 2A  : icates r emoved *
20000040 - 2A 2A 00 00 0A 0A 4F 43  52 41 4D 32 00 00 00 00  : **....OC RAM2....
20000050 - 30 30 30 00 30 30 00 00  30 00 00 00 30 30 30 30  : 000.00.. 0...0000
20000060 - 00 00 00 00 20 2D 20 00  20 20 20 00 20 3A 20 00  : .... - .    . : .
20000070 - 2E 2E 2E 09 20 00 00 00  20 64 75 70 6C 69 63 61  : .... ...  duplica
20000080 - 74 65 20 6C 69 6E 65 28  73 29 20 72 65 6D 6F 76  : te line( s) remov
20000090 - 65 64 2E 0A 00 00 00 00  00 01 00 00 30 01 00 20  : ed...... ....0.. 
200000A0 - 12 00 00 00 00 06 00 00  60 1F 00 60 0A 00 00 00  : ........ `..`....
200000B0 - 00 02 00 00 14 1F 00 60  4B 00 00 00 00 07 00 00  : .......` K.......
200000C0 - C8 1E 00 60 4B 00 00 00  00 03 00 00 C4 1E 00 60  : ...`K... .......`
200000D0 - 00 00 00 00 01 03 09 04  AC 1E 00 60 00 00 00 00  : ........ ...`....
200000E0 - 02 03 09 04 94 1E 00 60  00 00 00 00 03 03 09 04  : .......` ........
200000F0 - 44 01 00 20 00 00 00 00  00 00 00 00 00 00 00 00  : D.. .... ........
20000100 - 00 00 00 00 0D 0A 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000110 - 8D 18 00 00 85 18 00 00  81 18 00 00 7D 18 00 00  : ........ ....}...
20000120 - 79 18 00 00 75 18 00 00  71 18 00 00 6D 18 00 00  : y...u... q...m...
20000130 - 12 01 00 02 EF 02 01 40  C0 16 83 04 80 02 01 02  : .......@ ........
20000140 - 03 01 00 00 10 03 39 00  32 00 31 00 32 00 30 00  : ......9. 2.1.2.0.
20000150 - 37 00 30 00 00 00 00 00  00 00 00 00 10 01 00 20  : 7.0..... ....... 
20000160 - 00 00 00 00 E8 03 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000170 - 80 D1 F0 08 00 46 C3 23  00 00 00 00 64 04 00 20  : .....F.# ....d.. 
20000180 - CC 04 00 20 34 05 00 20  00 00 00 00 00 00 00 00  : ... 4..  ........
20000190 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
...  7 duplicate line(s) removed.
20000210 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000220 - 01 00 00 00 00 00 00 00  0E 33 CD AB 34 12 6D E6  : ........ .3..4.m.
20000230 - EC DE 05 00 0B 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
20000240 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
...  26 duplicate line(s) removed.
200003F0 - 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  : ........ ........
```
