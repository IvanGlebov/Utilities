// MASTER on I2C bus code
/*
#include <Arduino.h>
#include <Wire.h>

byte i2c_rcv;             // data recieved from I2C bus
unsigned long time_start; // start time in mSec
int statusLed;
byte counter;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  i2c_rcv = 255;
  time_start = millis();
  statusLed = 0;
  pinMode(BUILTIN_LED, OUTPUT);
  counter = 0;

}

void loop() {

  counter++;
  // First arg is slave ID, second arg - number of bytes we are going te read
  Wire.requestFrom(0x01, 1); // Request data from board with addred 0x01
  if (Wire.available()){ // If data arrived
    i2c_rcv = Wire.read();
    // We revieved one byte of data 
    Serial.println("Recieved byte : " + String(i2c_rcv));
  }
  
  delay(1000);
}

*/


// MASTER
#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}


