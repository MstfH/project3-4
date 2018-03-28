/* --------------------------------------
 *             MFRC522      Arduino  
 *             Reader/PCD   Uno/101      
 * Signal      Pin          Pin           
 * --------------------------------------
 * RST/Reset   RST          9         
 * SPI SS      SDA(SS)      10          
 * SPI MOSI    MOSI         11 / ICSP-4 
 * SPI MISO    MISO         12 / ICSP-1 
 * SPI SCK     SCK          13 / ICSP-3 
 */

#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9 //Ignore, RST pin used instead

//Keypad initialization 
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key; 


void setup(){
  Serial.begin(9600);
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
}

void loop(){
  char key = keypad.getKey();

  //Keypress detected. Print key
  if (key != NO_KEY){
    Serial.print("KEY: ");
    Serial.println(key);
  }

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()){
    return;
  }

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial()){
    return;
  }

  // Check is the PICC of Classic MIFARE type
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("RFID: Error: Not a MIFARE Type cardd"));
    return;
  }

  // Print NUID
  Serial.print("RFID: ");
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  // Stop repeatative printing
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

/*
 * Print NUIN as Hexadecimal
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i], HEX);
  }
}
