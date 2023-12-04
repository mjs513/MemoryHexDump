/*
  SD File Hex Dump

  This example is specific to the Teensy 3.x and 4.x boards
  as it uses the Teensy version of SD and SDFat.
  
  This example code is in the public domain.
*/

#include <MemoryHexDump.h>

char filename[256] = "2001/stop.wav";

//=============================================================================
// SD classes
//=============================================================================
#include <SD.h>
#define USE_BUILTIN_SDCARD
#if defined(USE_BUILTIN_SDCARD) && defined(BUILTIN_SDCARD)
#define CS_SD  BUILTIN_SDCARD
#else
#define CS_SD 10
// SDClasses
// edit SPI to reflect your configuration (following is for T4.1)
#define SD_MOSI 11
#define SD_MISO 12
#define SD_SCK  13
#endif

#define SPI_SPEED SD_SCK_MHZ(16)  // adjust to sd card 
SDClass sd;
DMAMEM uint8_t buffer[512];

void storage_configure()
{
  DateTimeFields date;
  breakTime(Teensy3Clock.get(), date);
  const char *monthname[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
  Serial.printf("Date: %u %s %u %u:%u:%u\n",
                date.mday, monthname[date.mon], date.year + 1900, date.hour, date.min, date.sec);


#if defined SD_SCK
  SPI.setMOSI(SD_MOSI);
  SPI.setMISO(SD_MISO);
  SPI.setSCK(SD_SCK);
#endif
  if (!sd.begin(CS_SD))
  {
    Serial.printf("SD Failed to start");  Serial.println();
    pinMode(LED_BUILTIN, OUTPUT);
    for (;;) {
      digitalWriteFast(LED_BUILTIN, HIGH);
      delay(100);
      digitalWriteFast(LED_BUILTIN, LOW);
      delay(100);
      digitalWriteFast(LED_BUILTIN, HIGH);
      delay(100);
      digitalWriteFast(LED_BUILTIN, LOW);
      delay(500);
    }
  }
}

void setup()
{

  // Open serial communications and wait for port to open
  while (!Serial && millis() < 5000) ;

  if (CrashReport) Serial.print(CrashReport);
  Serial.print("\n" __FILE__ " " __DATE__ " " __TIME__);
#if defined(ARDUINO_TEENSY41)
  Serial.println("  - Teensy 41");  
#elif defined(ARDUINO_TEENSY40)
  Serial.println("  - Teensy 40");  
#elif defined(TEENSY_MICROMOD)
  Serial.println("  - Teensy MicroMod");  
#else
  Serial.println();
#endif  
  delay(3000);

  storage_configure();

  Serial.println("\nSetup done");
}

void loop()
{
  File file;
  listFiles();
  while (Serial.read() != -1) ;
  uint32_t file_offset = 0;
  Serial.printf("Enter new file name to dump or hit enter to dump: %s\n", filename);
  int ch;
  while ((ch = Serial.read()) == -1) ;
  if (ch >= ' ') {
    char *psz = filename;
    while (ch >= ' ') {
      *psz++ = ch;
      ch = Serial.read();
    }
    *psz = '\0';
  }
  while (Serial.read() != -1) ;

  Serial.printf("Dumping %s\n", filename);

  file = sd.open(filename);
  if (!file) {
    Serial.println("*** Failed to open ***");
  } else {
    bool auto_mode = false;
    for(;;) {
      size_t cb = file.read(buffer, sizeof(buffer));
      if (cb == 0) break;
      if (cb > sizeof(buffer)) {
        Serial.println("\n ####### Read returned error ######");
        break;
      }
      Serial.printf("\nFile Offset: %u\n", file_offset);
      MemoryHexDump(Serial, buffer, cb, true, nullptr, (uint32_t)-1, file_offset);
      if (auto_mode) {
        if (Serial.available()) break;
      } else {
        Serial.print("(Q/A):");
        while ((ch=Serial.read()) == -1);
        if ((ch == 'q') || (ch == 'Q')) break;
        if ((ch == 'a') || (ch == 'A')) auto_mode = true;
        while (Serial.read() != -1) ;
      }
      file_offset += cb;
    }
    file.close();
    Serial.println("Done.");
  }
}

void listFiles()
{
  /*
  Serial.print("\n Space Used = ");
  Serial.println(sd.usedSize());
  Serial.print("Filesystem Size = ");
  Serial.println(sd.totalSize());
  */
  printDirectory(&sd);
}


void printDirectory(FS * pfs) {
  Serial.println("Directory\n---------");
  printDirectory(pfs->open("/"), 0);
  Serial.println();
}

void printDirectory(File dir, int numSpaces) {
  while (true) {
    File entry = dir.openNextFile();
    if (! entry) {
      //Serial.println("** no more files **");
      break;
    }
    printSpaces(numSpaces);
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numSpaces + 2);
    } else {
      // files have sizes, directories do not
      printSpaces(36 - numSpaces - strlen(entry.name()));
      Serial.print("  ");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void printSpaces(int num) {
  for (int i = 0; i < num; i++) {
    Serial.print(" ");
  }
}
