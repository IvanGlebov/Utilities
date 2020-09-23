// MASTER
#include <Arduino.h>
#include <Wire.h>
// Structure for packet variables saving
struct packetData{
  int id;
  float airTemp;
  float airHum;
  float groundTemp;
  float groundHum;
  float lightLevel;
};

void parsePackage(packetData&, String);
void showPackage(packetData);
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 28);    // request 6 bytes from slave device #8
  String arrivedData = "";
  packetData data1;
  while (Wire.available() > 0) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    arrivedData += c;   // Add symbol to arrivedData string for furute work
    Serial.print(c);         // print the character
  }
  Serial.println();
  // parsePackage(data1, arrivedData);
  parsePackage(data1, arrivedData);
  showPackage(data1);
  //Serial.println("Attempt to read data");
  delay(1000);
}

void parsePackage(packetData& d1, String arrData){
  String temp = "";
  
  // ID reading
  //d1.id = static_cast<int>(arrData[0]) + static_cast<int>(arrData[1]);
  char tempChar[10];
  tempChar[0] = arrData[0];
  tempChar[1] = arrData[1];
  
  d1.id = atof(tempChar);
  temp = "";

  // Air temperature reading
  temp = arrData[3] + arrData[4];
  tempChar[0] = arrData[3];
  tempChar[1] = arrData[4];
  d1.airTemp = atof(tempChar);
  // temp = "";
  if(arrData[2] == '-') d1.airTemp = -d1.airTemp;
  // temp = arrData[5] + arrData[6];
  tempChar[0] = arrData[5];
  tempChar[1] = arrData[6];
  d1.airTemp += atof(tempChar)/100;
  // temp = "";

  // Air humidity reading
  temp = arrData[7] + arrData[8] + arrData[9];
  d1.airHum = temp.toFloat();
  temp = "";
  temp = arrData[10] + arrData[11];
  d1.airHum += temp.toFloat()/100;
  temp = "";

  // Ground temperature reading
  temp = arrData[13] + arrData[4];
  d1.groundTemp = temp.toFloat();
  temp = "";
  if(arrData[12] == '-') d1.groundTemp = -d1.groundTemp;
  temp = arrData[15] + arrData[16];
  d1.groundTemp += temp.toFloat()/100;
  temp = "";

  // Ground humidity reading
  temp = arrData[17] + arrData[18] + arrData[19];
  d1.groundHum = temp.toFloat();
  temp = "";
  temp = arrData[20] + arrData[21];
  d1.groundHum += temp.toFloat()/100;
  temp = "";

  // Light level reading
  temp = arrData[22] + arrData[23] + arrData[24] + arrData[25];
  d1.lightLevel = temp.toFloat();
  temp = "";
  temp = arrData[26] + arrData[27];
  d1.lightLevel += temp.toFloat()/100;
  // return d1;
}
void showPackage(packetData p1){
  Serial.println("/-----------PACKAGE-DATA-----------");
  Serial.println("ID of sender       : " + String(p1.id));
  Serial.println("Air temperature    : " + String(p1.airTemp));
  Serial.println("Air humidity       : " + String(p1.airHum));
  Serial.println("Ground temperature : " + String(p1.groundTemp));
  Serial.println("Ground humidity    : " + String(p1.groundHum));
  Serial.println("Light level        : " + String(p1.lightLevel));
  Serial.println("/---------------------------------/");
}
