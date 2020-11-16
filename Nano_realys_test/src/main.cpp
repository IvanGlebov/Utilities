#include <Arduino.h>
#define r1 2
#define r2 3
void setup() {
  Serial.begin(9600);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
}

void loop() {
  digitalWrite(r1, HIGH);
  delay(1000);
  digitalWrite(r1, LOW);
  delay(1000);
  digitalWrite(r2, HIGH);
  delay(1000);
  digitalWrite(r2, LOW);
  delay(1000);
}