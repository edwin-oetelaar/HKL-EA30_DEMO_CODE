// EA30 measure analog input use pin A2
/*install  ADS1X15 library*/
#include "ADS1X15.h"
ADS1115 ADS(0x48);
void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("Welcome Use HANKERILA EA30");

  Wire.begin(4,5);
  ADS.begin();
}


void loop() 
{
  ADS.setGain(0);  //Set gain  Default MaxVoltage 6.14V

  int16_t val_0 = ADS.readADC(2);  // measure PIN A2

  float g= ADS.getMaxVoltage();
  Serial.print("g="); Serial.println(g); 

  float f = ADS.toVoltage(1);  //  voltage factor MaxVoltage/32767
  Serial.print("f="); Serial.println(f,5); 
  
  if(val_0 >=0){
    Serial.print("Analog01: "); 
    Serial.print(val_0);
    Serial.print("\t");
    Serial.print(val_0 * f, 3); 
    Serial.println("V");
    Serial.println();
  }

  delay(1000);
}


