/*************************************************** 
  This is a library for the HTU21D-F Humidity & Temp Sensor

  Designed specifically to work with the HTU21D-F sensor from Adafruit
  ----> https://www.adafruit.com/products/1899

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _HTU21DF_H
#define _HTU21DF_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define HTU21DF_I2CADDR              0x40
#define HTU21DF_READTEMP             0xE3
#define HTU21DF_READHUM              0xE5
#define HTU21DF_WRITEREG             0xE6
#define HTU21DF_READREG              0xE7
#define HTU21DF_RESET                0xFE

#define HTU21D_POLL_LIMIT            8         //i2c retry limit

#define HTU21D_READ_TEMP             0xFE      //indicates to read the temperature from the sensor before humidity compensation, see https://github.com/enjoyneering/HTU21D/pull/3
#define HTU21D_ERROR                 0xFF      //returns 255, if CRC8 or communication error is occurred

class HTU21DF {
 public:
  HTU21DF();
  boolean begin(uint8_t sda = SDA, uint8_t scl = SCL);
  float readTemperature(void);
  float readHumidity(void);
  void reset(void);
 private:
  //boolean readData(void);
  //float humidity, temp;
};

#endif
