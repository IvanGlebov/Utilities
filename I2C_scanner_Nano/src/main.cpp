#include <Arduino.h>
#include <Wire.h>
#define localBus 3
#define masterBus 4
// 0x40, 0x41, 0x44

void setup(){
    Wire.begin();   
    Serial.begin(9600);
    while (!Serial);
    Serial.println("\nI2C Scanner"); 

    pinMode(localBus, OUTPUT);
    pinMode(masterBus, OUTPUT);
    digitalWrite(localBus, HIGH);
    digitalWrite(masterBus, HIGH);
} 
 
void loop(){
    digitalWrite(localBus, HIGH);
    digitalWrite(masterBus, HIGH);
    byte error, address;
    int nDevices;
 
    Serial.println("Scanning...");
 
    nDevices = 0;
    for(address = 8; address < 127; address++ ){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
 
        if (error == 0){
            Serial.print("I2C device found at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.print(address,HEX);
            Serial.println(" !");
 
            nDevices++;
        }
        else if (error==4) {
            Serial.print("Unknow error at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.println(address,HEX);
        } 
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
 
    delay(5000);
}