/*
--Initially clean64Buf() function clears the mempory data of the scanned NTAG.
--Then, writetoNTAG() function writes the defined strings in buffer and bufEmail in to the memory.
--Finally, readfromNTAG() funciton reads the memory of the NTAG. 
*/

#include <Wire.h>
#include "MFRC522_I2C.h"
#include <SoftwareSerial.h>

#define RST_PIN PA8 // Set Reset Pin

// 0x28 is i2c address on SDA. Check your address with i2cscanner if not match.
MFRC522 mfrc522(0x2D, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;          //create a MIFARE_Key struct named 'key', which will hold the card information
MFRC522::StatusCode status; //variable to get card status
////////////////////////////////////////////////////////////////////////////
int bufCleansize = 66 ;
byte bufClean[64]= {0};  //data transfer buffer (16+2 bytes data+CRC)
int TotalPageReqClean = bufCleansize/4   ;
///////////////////////////////////////////////////////////////////////////
int buffersize = 22 ;
byte buffer[22];  //data transfer buffer (16+2 bytes data+CRC)
byte size = sizeof(buffer);
int TotalPageReq = buffersize/4   ;
uint8_t pageAddr = 0x04;  //In this example we will write/read 16 bytes (page 6,7,8 and 9).
                            //Ultraligth mem = 16 pages. 4 bytes per page.  
                            //Pages 0 to 4 are for special functions.    
///////////////////////////////////////////////////////////////////////////
int buffersizeEmail = 29 ;
byte bufEmail[29];  //data transfer buffer (16+2 bytes data+CRC)
byte sizeEmail = sizeof(bufEmail);
int TotalPageReqEmail = buffersizeEmail/4   ;
///////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);         // Initialize serial communications with the PC
  Serial2.begin(115200);
  Wire.setSDA(PB9);               // Set SDA
  Wire.setSCL(PB6);               // Set SCL
  Wire.begin();                   // Initialize I2C

    mfrc522.PCD_Init(); // Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    Serial2.println(F("BEWARE: Data will be written to the PICC, in sector #1"));
    memcpy(buffer,"Hello World! ",20);
    memcpy(bufEmail," Hello.World@Earth.com",27);
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  // Clean all pages
   clean64Buf();
  // Write data ***************************************************
   writetoNTAG(pageAddr,TotalPageReq,buffer);

   writetoNTAG(pageAddr+TotalPageReq,TotalPageReqEmail,bufEmail);
   
   // Read data ***************************************************
   readfromNTAG(pageAddr,size,buffer,buffersize);
   readfromNTAG(pageAddr+TotalPageReq,sizeEmail,bufEmail,buffersizeEmail);
  
  Serial2.println();

/*
	-- Dump debug info about the card; 
  -- Uncomment the following line if you want to see the memory HEX data. 
*/
	//mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

/*PICC_HaltA() is automatically called*/
  mfrc522.PICC_HaltA(); // Halt the system for the next scan of the card
}