// SLAVE board
#include <Arduino.h> // Main library
#include <Wire.h> // For all I2C sensors and I2C bus to master
#include <BH1750.h> // For BH1750 digital light sensor
#include <SPI.h> //
#include <Adafruit_Sensor.h> // For INA219 sensor libraries
#include <Adafruit_INA219.h>
#include <WEMOS_SHT3X.h> // For SHT30 digital temp and humidity sensor
#include <math.h> // For using atof()

#define sensorsBus 3
#define masterBus 4
#define debug true

// Structure for packet variables saving
struct packetData{
  int id;
  float airTemp;
  float airHum;
  float groundTemp;
  float groundHum;
  float lightLevel;
};

// Structure for packet from INA sensors
struct inaPack{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
};
Adafruit_INA219 ina219_h(0x40);
Adafruit_INA219 ina219_t(0x41);

// BH1750 light sensor config
BH1750 lightSensor;
float getLight();

// TH-12 sensor block
// INA219 sensors
// Adafruit_INA219 ina219_h(0x40);
// Adafruit_INA219 ina219_t(0x41);
float getGroundTemp();
float getGroundHum();
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// SHT30 sensor
SHT3X sht30(0x44);
// Function recieve array of 2 elements and fill it
// void getSHT(float *);



void requestEvent();
// New format - sending data to function in the structure
String structFormPacket(packetData d1);
// Old version with sending data right to function, not in the structure format
String formPacket(int id, float tempAir, float humAir, float tempGround, float humGround, float lightLevel);

void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  digitalWrite(sensorsBus,HIGH);
  digitalWrite(masterBus, HIGH);


  lightSensor.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  if (! ina219_t.begin()) {
    if (debug) Serial.println("Failed to find INA219_1 chip");
  }
  if (! ina219_h.begin()){
    if (debug) Serial.println("Failed to find INA219_2 chip");
  }
  


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
  delay(99);
  packetData data1;
  data1.airHum = 11.2;
  data1.airTemp = 24.3;
  data1.groundHum = 45.2;
  data1.groundTemp = 23.8;
  data1.id = 1.0;
  data1.lightLevel = 1297.45;
  String packet1 = structFormPacket(data1);
  // String packet = formPacket(1, 1.1, 1.1, 1.1, 1.1, 1.1);
  int len = 28;
  for(int i=0; i < len; i++){
    Wire.write(packet1[i]);
    Serial.print(packet1[i]);
  }
  Serial.println();
}
