// SLAVE board
#include <Arduino.h>
#include <Wire.h>
#include <math.h>
// Structure for packet variables saving
struct packetData{
  int id;
  float airTemp;
  float airHum;
  float groundTemp;
  float groundHum;
  float lightLevel;
};

void requestEvent();
// New format - sending data to function in the structure
String structFormPacket(packetData d1);
// Old version with sending data right to function, not in the structure format
String formPacket(int id, float tempAir, float humAir, float tempGround, float humGround, float lightLevel);

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 3, 8);          // int sda, int scl, uint8_t addres
  //Wire.begin(8);              // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  // Do nothing while no signals from master
}

String structFormPacket(packetData d1){
  String temp = "";
  double l, r;

  // ID adding to string
  if(d1.id < 10) temp += "0" + String(d1.id);
  else temp += String(d1.id);

  // Air temperature adding to string
  if(d1.airTemp >= 0) temp += "+";
  else temp += "-";
  //  abs(x) ((x)>0?(x):-(x))
  float airTemp = abs(d1.airTemp);
  l = int(airTemp); // Left part of the number
  r = airTemp - l; // right part of the nember
  r *= 100; // Convert r value to full integer
  r = int(r);
  if(l < 10) temp += "0" + String(static_cast<int>(l));
  else if (l < 100) temp += String(static_cast<int>(l));
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  // Air humidity adding to string
  l = int(d1.airHum);
  r = int((d1.airHum-l)*100);
  if(l < 10) temp += "00" + String(static_cast<int>(l));
  else if (l < 100) temp += "0" + String(static_cast<int>(l));
  else if (l == 100) temp += "100/";
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  //tempGround
  if(d1.groundTemp >= 0) temp += "+";
  else temp += "-";
  //  abs(x) ((x)>0?(x):-(x))
  float groundTemp = abs(d1.groundTemp);
  l = int(groundTemp); // Left part of the number
  r = groundTemp - l; // right part of the nember
  r *= 100; // Convert r value to full integer
  r = int(r);
  // temp += "T";
  if(l < 10) temp += "0" + String(static_cast<int>(l));
  else if (l < 100) temp += String(static_cast<int>(l));
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  // Ground humidity adding to string
  l = int(d1.groundHum);
  r = int((d1.groundHum-l)*100);
  if(l < 10) temp += "00" + String(static_cast<int>(l));
  else if (l < 100) temp += "0" + String(static_cast<int>(l));
  else if (l == 100) temp += "100";
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  // Light level adding to string
  l = int(d1.lightLevel);
  r = int((d1.lightLevel-l)*100);
  if(l < 10) temp += "000" + String(static_cast<int>(l));
  else if (l < 100) temp += "00" + String(static_cast<int>(l));
  else if (l < 1000) temp += "0" + String(static_cast<int>(l));
  else if (l < 10000) temp += String(static_cast<int>(l));
  else temp += "9999/";
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  return temp;
}

String formPacket(int id, float tempAir, float humAir, float tempGround, float humGround, float lightLevel){

  String temp = "";
  double l, r;

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
  if(l < 10) temp += "0" + String(static_cast<int>(l));
  else if (l < 100) temp += String(static_cast<int>(l));
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  // Air humidity adding to string
  l = int(humAir);
  r = int((humAir-l)*100);
  if(l < 10) temp += "00" + String(static_cast<int>(l));
  else if (l < 100) temp += "0" + String(static_cast<int>(l));
  else if (l == 100) temp += "100/";
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

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
  if(l < 10) temp += "0" + String(static_cast<int>(l));
  else if (l < 100) temp += String(static_cast<int>(l));
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  // Ground humidity adding to string
  l = int(humGround);
  r = int((humGround-l)*100);
  if(l < 10) temp += "00" + String(static_cast<int>(l));
  else if (l < 100) temp += "0" + String(static_cast<int>(l));
  else if (l == 100) temp += "100";
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  // Light level adding to string
  l = int(humGround);
  r = int((humGround-l)*100);
  if(l < 10) temp += "000" + String(static_cast<int>(l));
  else if (l < 100) temp += "00" + String(static_cast<int>(l));
  else if (l < 1000) temp += "0" + String(static_cast<int>(l));
  else if (l < 10000) temp += String(static_cast<int>(l));
  else temp += "9999/";
  if(r < 10) temp += "0" + String(static_cast<int>(r));
  else if (r < 100)  temp += String(static_cast<int>(r));

  return temp;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  // Switch to sensors bus
  Wire.begin(2,1);
  packetData data1;
  data1.airHum = 11.2;
  data1.airTemp = 24.3;
  data1.groundHum = 45.2;
  data1.groundTemp = 23.8;
  data1.id = 1.0;
  data1.lightLevel = 1297.45;
  String packet1 = structFormPacket(data1);
  // Switch back to master-slave bus and send data back
  Wire.begin(2,1,8);
  int len = 28;
  for(int i=0; i < len; i++){
    Wire.write(packet1[i]);
    Serial.print(packet1[i]);
  }
  Serial.println();
}
