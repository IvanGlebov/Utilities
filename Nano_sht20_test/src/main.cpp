#include <Arduino.h>
#include "uFire_SHT20.h"
uFire_SHT20 sht20;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sht20.begin();
}

void loop() {
  sht20.measure_all();
  Serial.println(String(sht20.tempC) + " C");
  Serial.println(String(sht20.RH) + " %");
  delay(1000);
}