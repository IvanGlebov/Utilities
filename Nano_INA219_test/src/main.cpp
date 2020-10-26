#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219(0x40);
Adafruit_INA219 ina219_2(0x41);

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup(void) 
{
  Serial.begin(9600);
  // while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      // delay(1);
  // }

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219_1 chip");
    while (1) { delay(10); }
  }
  if (! ina219_2.begin()) {
    Serial.println("Failed to find INA219_2 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  ina219.setCalibration_16V_400mA();
  ina219_2.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("------------------------------------");
  // Serial.println("Humidity : " + String(mapFloat(monitor.busVoltage(), 0, 4.36, 0, 100)));
  Serial.println("Humidity    : " + String(mapFloat(busvoltage, 0, 10, 0, 100)));
  // Serial.println("Humidity : " + String(map(busvoltage, 0, 10, 0, 100)));
  Serial.println("------------------------------------");

  float shuntvoltage1 = 0;
  float busvoltage1 = 0;
  float current_mA1 = 0;
  float loadvoltage1 = 0;
  float power_mW1 = 0;

  shuntvoltage1 = ina219_2.getShuntVoltage_mV();
  busvoltage1 = ina219_2.getBusVoltage_V();
  current_mA1 = ina219_2.getCurrent_mA();
  power_mW1 = ina219_2.getPower_mW();
  loadvoltage1 = busvoltage1 + (shuntvoltage1 / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage1); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage1); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage1); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA1); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW1); Serial.println(" mW");
  Serial.println("------------------------------------");
  // Serial.println("Humidity : " + String(mapFloat(monitor.busVoltage(), 0, 4.36, 0, 100)));
  Serial.println("TemperatureFloat    : " + String(mapFloat(busvoltage1, 10, 0, -40, 80)));
  Serial.println("temperature         : " + String(map(busvoltage1, 10, 0, -40, 80)));
  // Serial.println("Humidity : " + String(map(busvoltage, 0, 10, 0, 100)));
  Serial.println("------------------------------------");
  delay(2000);
}