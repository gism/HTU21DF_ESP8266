#include "HTU21DF.h"
#if defined(__AVR__)
#include <util/delay.h>
#endif

HTU21DF::HTU21DF() {
}

boolean HTU21DF::begin(uint8_t sda, uint8_t scl) {
  Wire.begin(SDA, SCL);
  Wire.setClock(100000UL);              //experimental! ESP8266 i2c bus speed: 100kHz..400kHz/100000UL..400000UL, default 100000UL
  Wire.setClockStretchLimit(230);       //experimental! default 230usec
  
  Wire.beginTransmission(HTU21DF_I2CADDR);
  return Wire.endTransmission(true) == 0; //safety check, make sure the sensor is connected
}

void HTU21DF::reset(void) {
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_RESET);
  Wire.endTransmission();
  delay(15);
}


float HTU21DF::readTemperature(void) {
  // Serial.println("SEND REQ TEMP");
  
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READTEMP);
  Wire.endTransmission();
  //Serial.println( (Wire.endTransmission(true)));  

  int8_t   tryCounter    = HTU21D_POLL_LIMIT;
  /* read temperature measurement to "wire.h" rxBuffer */
  do
  {
    tryCounter--;
    if (tryCounter == 0) break; //return HTU21D_ERROR;                      //error handler
    
    delay(100); // add delay between request and actual read!
    
    //Serial.println("SEND REQ READ");
    Wire.requestFrom(HTU21DF_I2CADDR, 3);//, true);         //true = stop message after transmission & releas the I2C bus
    //Serial.println("WAIT REPLY");
  
    //Serial.print("AVAILABLE: ");
    //Serial.println(Wire.available()); 
  }
  while (Wire.available() == 0);                           //check rxBuffer

  //Serial.println("READ REPLY:");

  uint16_t rawTemperature  = Wire.read() << 8;
  rawTemperature |= Wire.read();

  //Serial.print("RAW TEMP: ");
  //Serial.println(rawTemperature); 
  //Serial.println(rawTemperature, HEX); 

  uint8_t crc = Wire.read();

  return 0.002681 * (float)rawTemperature - 46.85;  
}
  

float HTU21DF::readHumidity(void) {
  //Serial.println("SEND REQ HUM");
  
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READHUM);
  Wire.endTransmission();
  //Serial.println((Wire.endTransmission(true)));  

  int8_t   tryCounter    = HTU21D_POLL_LIMIT;
  /* read temperature measurement to "wire.h" rxBuffer */
  do
  {
    tryCounter--;
    if (tryCounter == 0) break; //return HTU21D_ERROR;                      //error handler
    
    delay(100); // add delay between request and actual read!
    
    //Serial.println("SEND REQ READ");
    Wire.requestFrom(HTU21DF_I2CADDR, 3);//, true);         //true = stop message after transmission & releas the I2C bus
    //Serial.println("WAIT REPLY");
  
    //Serial.print("AVAILABLE: ");
    //Serial.println(Wire.available()); 
  }
  while (Wire.available() == 0);                           //check rxBuffer

  //Serial.println("READ REPLY:");

  uint16_t rawHumidity = Wire.read() << 8;
  rawHumidity |= Wire.read();

  uint8_t crc = Wire.read();
  
  //Serial.print("RAW HUM: ");
  //Serial.println(rawHumidity); 
  //Serial.println(rawHumidity, HEX); 

  rawHumidity ^= 0x02;//clear status bits, humidity always returns xxxxxx10 in the LSB field
  
  return 0.001907 * (float)rawHumidity - 6;
}



/*********************************************************************/
