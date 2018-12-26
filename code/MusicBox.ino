#include <WaveHC.h>
#include <WaveUtil.h>
#include <Wire.h>
#include <Adafruit_PN532.h>


#define IRQ 6 // this trace must be cut and rewired!
#define RESET 8

Adafruit_PN532 nfc(IRQ, RESET);

SdReader card; // This object holds the information for the card
FatVolume vol; // This holds the information for the partition on the card
FatReader root; // This holds the information for the volumes root directory
FatReader file; // This object represent the WAV file for a pi digit or period
WaveHC wave; // This is the only wave (audio) object, since we will only play one at a time

/*
* Define macro to put error messages in flash memory
*/
#define error(msg) error_P(PSTR(msg))

//////////////////////////////////// SETUP

void setup() {
  // set up Serial library at 9600 bps
  Serial.begin(9600);
  
  if (!card.init()) {
    error("Card init. failed!");
  }
  if (!vol.init(card)) {
    error("No partition!");
  }
  if (!root.openRoot(vol)) {
    error("Couldn't open dir");
  }
  
  // find Adafruit RFID/NFC shield
  nfc.begin();

/*
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  //nfc.SAMConfig();
*/
}

/////////////////////////////////// LOOP

unsigned digit = 0;

void loop() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; // Buffer to store the returned UID
  uint8_t uidLength; // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // wait for RFID card to show up!
  Serial.println("Waiting for an ISO14443A Card ...");

    
  // Wait for an ISO14443A type cards (Mifare, etc.). When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    // Found a card!

    Serial.print("Card UID: ");
    // turn the four byte UID of a mifare classic into a single variable #
    Serial.println(charUID(uid, &uidLength));
  }
}

/////////////////////////////////// HELPERS

/*
* print error message and halt
*/
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
/*
* print error message and halt if SD I/O error
*/
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}
/*
* Play a file and wait for it to complete
*/
void playcomplete(char *name) {
  playfile(name);
  while (wave.isplaying);
  
  // see if an error occurred while playing
  sdErrorCheck();
}
/*
* Open and start playing a WAV file
*/
void playfile(char *name) {
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  if (!file.open(root, name)) {
    PgmPrint("Couldn't open file ");
    Serial.println(name);
    return;
  }
  if (!wave.create(file)) {
    PgmPrintln("Not a valid WAV");
    return;
  }
  // ok time to play!
  wave.play();
}

char charUID(uint8_t uid[], uint8_t uidLength) {
  char hexString[9];
  for (int i = 0; i < uidLength; i++) {
    char hexBuffer[3];
    itoa(uid[i], hexBuffer, 16);
    if (!isPrintable(hexBuffer[1])) {
      hexBuffer[1] = hexBuffer[0];
      hexBuffer[0] = '0';
    }
    hexString[i*2] = toupper(hexBuffer[0]);
    hexString[i*2+1] = toupper(hexBuffer[1]);
   }
   return hexString;
}
