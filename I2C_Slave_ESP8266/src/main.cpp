// SLAVE I2C bus device code
#include <Arduino.h>
#include <Wire.h>

byte i2c_rcv;
unsigned long time_start;
int statusLED;
byte counter;

void dataRqst();

void setup() {
  Wire.begin(0x01); // Join I2C bus with 0x01 address
  Wire.onRequest(dataRqst);
  
}

void loop() {

  int t = millis();
  if(millis() - t >= 1000) {
    counter++;
    t = millis();
  }
  
}



void dataRqst(){
  Wire.write(counter);
}


