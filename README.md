# MFRC522 I2C library written based on the main Arduino library in [MFRCC522_i2c](https://www.arduino.cc/reference/en/libraries/mfrc522_i2c/)
### This repository provides examples of NFC reading and writing via an I2C bus connected to an STM32 microcontroller.

The new examples have been tested on a custom board equipped with STM32F407VG microcontroller. 

__Set the PIN for the RST and i2c address!__
```c++
#define RST_PIN PA6 //This line in the code is to set the Reset pin of the MFRC522

// 0x2D is the i2c address of the NFC Reader. Check your address with i2cscanner if it does not match.
MFRC522 mfrc522(0x2D, RST_PIN);   // Create MFRC522 instance.

__In the STM32 Custom board set the SDA and SCL pins using the following lines in the examples:__
  Wire.setSDA(PB9); // Set SDA
  Wire.setSCL(PB6); // Set SCL
  Wire.begin();     // Initialize I2C             
```
Thanks to @kkloesener for the development of [MFRC522 i2c](https://github.com/kkloesener/MFRC522_I2C)
and @arozcan for adding the examples in [MFRC522 i2c Library](https://github.com/arozcan/MFRC522-I2C-Library)
