#include <Arduino.h>
#include "PCF8574.h"
#include <Wire.h>

PCF8574 pcf_1(0x20);
PCF8574 pcf_2(0x21);

void setup() {
  Serial.begin(115200);
  pcf_1.begin();
  pcf_2.begin();
  delay (5000);
}

void loop() {
  for (int i=0; i <8; i++){
    pcf_1.write(i, LOW);
    delay(2000);
    pcf_1.write(i, HIGH);
    delay(2000);
  }
  for (int i=0; i<8; i++){
    pcf_2.write(i, LOW);
    delay(2000);
    pcf_2.write(i, HIGH);
    delay(2000);
  }
  delay(2000);
}