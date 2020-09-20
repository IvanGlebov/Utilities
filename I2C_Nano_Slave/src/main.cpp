// SLAVE
#include <Arduino.h>
#include <Wire.h>
#include <math.h>

void requestEvent();

String formPacket(int id, float tempAir, float humAir, float tempGround, float humGround, float lightLevel);

void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}


String formPacket(int id, float tempAir, float humAir, float tempGround, float humGround, float lightLevel){
  String temp = "";
  double l, r;
  char temp1[5];

  // Device id
  sprintf(temp1, "%02d", id);
  temp += String(temp1[0]) + String(temp1[1]);
  
  // Air temperature parametrs
  if (tempAir >= 0) temp += "+";
  else temp += "-";
  r = modf(tempAir, &l);
  sprintf(temp1, "%02d", l);
  temp += String(temp[0]) + String(temp[1]);
  temp += "/";
  sprintf(temp1, "%02d", r);
  temp += String(temp1[0]) + String(temp1[1]);
  temp += ";";
  // Air humidity parametrs
  temp += "h";
  r = modf(humAir, &l);
  sprintf(temp1, "%03d", l);
  temp += String(temp1[0]) + String(temp1[1]) + String(temp1[2]);
  temp += "/";
  sprintf(temp1, "%02d", r);
  temp += String(temp1[0]) + String(temp1[1]);
  temp += ";";


  
  return temp;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  String packet = formPacket(1, 1.1, 1.1, 1.1, 1.1, 1.1);
  int len = 18;
  for(int i=0; i < len; i++){
    Wire.write(packet[i]);
    Serial.print(packet[i]);
  }
  Serial.println();
  //Wire.write("hello"); // respond with message of 6 bytes
  // as expected by master
}
