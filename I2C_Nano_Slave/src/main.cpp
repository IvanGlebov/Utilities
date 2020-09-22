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
  // delay(100);
}


String formPacket(int id, float tempAir, float humAir, float tempGround, float humGround, float lightLevel){
  String temp = "";
  double l, r;
  // int lint, rint;
  char temp1[5] = "";

  // ID adding to string
  if(id < 10) temp += "0" + String(id);
  else temp += String(id);

  // Air temperature adding to string
  if(tempAir >= 0) temp += "+";
  else temp += "-";
  //  abs(x) ((x)>0?(x):-(x))
  float airTemp = abs(tempAir);
  l = int(airTemp); // Left part of the number
  r = airTemp - l; // right part of the nember
  r *= 100; // Convert r value to full integer
  r = int(r);
  // temp += "t";
  // lint = l;
  // rint = r;
  if(l < 10) temp += "0" + String(static_cast<int>(l)) /* + "/" */;
  else if (l < 100) temp += String(static_cast<int>(l))/*  + "/" */;
  if(r < 10) temp += "0" + String(static_cast<int>(r))/*  + ";" */;
  else if (r < 100)  temp += String(static_cast<int>(r))/*  + ";" */;

  // Air humidity adding to string
  l = int(humAir);
  r = int((humAir-l)*100);
  // temp += "h";
  // lint = l;
  // rint = r;
  if(l < 10) temp += "00" + String(static_cast<int>(l))/*  + "/" */;
  else if (l < 100) temp += "0" + String(static_cast<int>(l))/*  + "/" */;
  else if (l == 100) temp += "100/";
  if(r < 10) temp += "0" + String(static_cast<int>(r))/*  + ";" */;
  else if (r < 100)  temp += String(static_cast<int>(r))/*  + ";" */;

  //tempGround
  if(tempGround >= 0) temp += "+";
  else temp += "-";
  //  abs(x) ((x)>0?(x):-(x))
  float groundTemp = abs(tempGround);
  l = int(groundTemp); // Left part of the number
  r = groundTemp - l; // right part of the nember
  r *= 100; // Convert r value to full integer
  r = int(r);
  // temp += "T";
  if(l < 10) temp += "0" + String(static_cast<int>(l))/*  + "/" */;
  else if (l < 100) temp += String(static_cast<int>(l))/*  + "/" */;
  if(r < 10) temp += "0" + String(static_cast<int>(r))/*  + ";" */;
  else if (r < 100)  temp += String(static_cast<int>(r))/*  + ";" */;

  // Ground humidity adding to string
  l = int(humGround);
  r = int((humGround-l)*100);
  // temp += "H";
  if(l < 10) temp += "00" + String(static_cast<int>(l))/*  + "/" */;
  else if (l < 100) temp += "0" + String(static_cast<int>(l))/*  + "/" */;
  else if (l == 100) temp += "100" /* / */;
  if(r < 10) temp += "0" + String(static_cast<int>(r))/*  + ";" */;
  else if (r < 100)  temp += String(static_cast<int>(r))/*  + ";" */;

  // Light level adding to string
  l = int(humGround);
  r = int((humGround-l)*100);
  // temp += "l";
  if(l < 10) temp += "000" + String(static_cast<int>(l))/* + "/"*/;
  else if (l < 100) temp += "00" + String(static_cast<int>(l))/* + "/"*/;
  else if (l < 1000) temp += "0" + String(static_cast<int>(l))/* + "/"*/;
  else if (l < 10000) temp += String(static_cast<int>(l))/* + "/"*/;
  else temp += "9999/";
  if(r < 10) temp += "0" + String(static_cast<int>(r))/* + ";"*/;
  else if (r < 100)  temp += String(static_cast<int>(r))/* + ";"*/;

/*
  // Device id
  sprintf(temp1, "%02d", id);
  temp += String(temp1[0]) + String(temp1[1]);
  
  // Air temperature parametrs
  if (tempAir >= 0.0) temp += "+";
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
  */

  // temp += "\r";
  return temp;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  String packet = formPacket(1, 1.1, 1.1, 1.1, 1.1, 1.1);
  int len = 28;
  for(int i=0; i < len; i++){
    Wire.write(packet[i]);
    Serial.print(packet[i]);
  }
  Serial.println();
  //Wire.write("hello"); // respond with message of 6 bytes
  // as expected by master
}
