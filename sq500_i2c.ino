#include <Wire.h>

void SetupSQ500() {
  Wire.beginTransmission(0x68);
  Wire.write(1 << 4 | 1 << 7 | 1 << 3);
  Wire.endTransmission(); 
}

float ReadSQ500() {
  int16_t result = 0;


  Wire.requestFrom(0x68, 3);
  
  while(!Wire.available()) {}
  uint8_t msb = Wire.read();
  Serial.print(msb, HEX);
 
  while(!Wire.available()) {}
  uint8_t lsb = Wire.read();
  Serial.print(lsb, HEX);

  result = msb << 8 | lsb;
  if (result < 0)
    result = 0;

  float ret = 0;

  ret = (result / (float)0xFFFF) *  2.048;
  ret *= 2000;
  
  if (Wire.available()) {
    uint8_t config = Wire.read();
    Serial.println();
  }
  return ret;
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println();
  Serial.print("Setup SQ500");
  SetupSQ500();
  Serial.print("Setup complete");
}

void loop() {
  Serial.println();
  Serial.print("Reading sensor: ");
  Serial.print(ReadSQ500());
  Serial.println();
  delay(1000);

}
