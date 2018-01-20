#include <HTU21DF.h>
#include <Wire.h>

HTU21DF htu = HTU21DF();

void setup() {
  Serial.begin(115200);
  Serial.println("HTU21D-F test");

  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1){
      delay(100);
    }
  }
}


void loop() {
  Serial.print("Temp: "); Serial.print(htu.readTemperature());
  delay(500);
  Serial.print("\t\tHum: "); Serial.println(htu.readHumidity());
  delay(500);
}
