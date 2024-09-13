void clean64Buf(){
    // Write data ***********************************************
  for (int i=0; i < TotalPageReqClean; i++) {
    //data is writen in blocks of 4 bytes (4 bytes per page)
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Ultralight_Write(3+i, &bufClean[i*4], 4);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Read() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
  }
  Serial.println(F("MIFARE_Ultralight_Write() Cleaned"));
  Serial.println();
}

void writetoNTAG(uint8_t pagestart,int TotalPages,byte *bufinput){//( ){
    for (int i=0; i < TotalPages; i++) {
    //data is writen in blocks of 4 bytes (4 bytes per page)
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Ultralight_Write(pagestart+i, &bufinput[i*4], 4);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Read() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
  }
  Serial.println(F("MIFARE_Ultralight_Write() OK "));
  Serial.println();
}

void readfromNTAG(uint8_t pagestart,byte sizeIn,byte *bufinput,int bufSize){
    Serial.println(F("Reading data ... "));
  //data in 4 block is readed at once.
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(pagestart, bufinput, &sizeIn);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  Serial.print(F("Read data: "));
  //Dump a byte array to Serial
  for (byte i = 0; i < bufSize-2; i++) {
    Serial.write(bufinput[i]);
  }
}


