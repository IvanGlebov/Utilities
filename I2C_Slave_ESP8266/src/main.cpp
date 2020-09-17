// SLAVE I2C bus device code
/*
#include <Arduino.h>
#include <Wire.h>

byte i2c_rcv;
unsigned long time_start;
int statusLED;
byte counter;

void dataRcv(int);
void dataRqst();

void setup() {
  Wire.begin(40); // Join I2C bus with 0x01 address
  Wire.onReceive(dataRcv);
  Wire.onRequest(dataRqst);

}

void loop() {

  int t = millis();
  if(millis() - t >= 1000) {
    counter++;
    t = millis();
    if (counter > 255)
      counter = 0;
  }
  
}

void dataRcv(int numBytes){
  while(Wire.available()){
    i2c_rcv = Wire.read();
  }
}

void dataRqst(){
  Wire.write(counter);
}
*/

// SLAVE
#include <Arduino.h>
#include <Wire.h>
void requestEvent();
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}

