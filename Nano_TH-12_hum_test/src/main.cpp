#include <Arduino.h>
#define hum A0
void setup() {
  Serial.begin(9600);
  pinMode(hum, INPUT);
}

void loop() {
  Serial.println("Humidity : " + String(map(analogRead(hum), 0, 1023, 100.00, 0.00)));
  delay(1000);
}