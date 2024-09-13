#include <Wire.h>
#include "MFRC522_I2C.h"

#define RST_PIN PA8 // Set Reset pin 

// 0x2D is i2c address on SDA. Check your address with i2cscanner if not match.
MFRC522 mfrc522(0x2D, RST_PIN);   // Create MFRC522 instance.

void setup() {
  Serial.begin(115200);           // Initialize serial communications with the PC
  Wire.setSDA(PB9);               // Set SDA
  Wire.setSCL(PB6);               // Set SCL
  Wire.begin();                   // Initialize I2C

	mfrc522.PCD_Init();		          // Init MFRC522
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  ShowReaderDetails();            // Show details of PCD - MFRC522 Card Reader details
}

void loop() {
  	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

void ShowReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Software Version: 0x"));
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown)"));
  Serial.println("");
  // When 0x00 or 0xFF is returned, communication probably failed
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
  }
}

