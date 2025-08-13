/*I2C device Scan*/
/*Install "PCF8574 library"*/
 
 #include "I2CScanner.h"
 #include <Wire.h>
 #include <PCF8574.h>

I2CScanner scanner;
PCF8574 pcf8574_re1(0x22,4,5);


void setup() 
{
	Serial.begin(115200);
  Wire.begin(4,5);
	while (!Serial) {};
  pcf8574_re1.begin();
	scanner.Init();
}

void loop() 
{
	scanner.Scan();
 	delay(1000);
}
