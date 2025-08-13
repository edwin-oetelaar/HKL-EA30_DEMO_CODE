//EA30 SCT SENSOR MEASSURE
/*INSTALL ADS1X15 library*/

#include "ADS1X15.h"
ADS1115 ADS(0x48);

// Use SCT013 30A/1V 
const float SCT013_VOLTAGE_PER_AMPERE = 1.0 / 30.0;

void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("Welcome to use HANKERILA HKL-EA30");

  Wire.begin(4, 5);
  ADS.begin();
}

void loop() 
{
   ADS.setGain(0); // Set MaxVoltage 6.14V

  // Read the SCT013 sensor connection channel (A0-A1 differential mode)
  int16_t diffVal = ADS.readADC_Differential_0_1();  

  // Converts the read digital value to the voltage value
  float voltage = ADS.toVoltage(diffVal);  

  // Convert voltage value to current value according to SCT013 parameter
  float current = voltage / SCT013_VOLTAGE_PER_AMPERE;  

  if(voltage >=0){
    Serial.print("SCT013 Voltage: "); Serial.print(voltage, 3); Serial.println(" V");
    Serial.print("SCT013 Current: "); Serial.print(current, 3); Serial.println(" A");
  }
  Serial.println();

  delay(1000);
}