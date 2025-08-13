/*A6 PCF8574 output control relays*/

#include "Arduino.h"
/*install pcf8574 library*/
#include "PCF8574.h"
// EA30 Relay output control
/*SDA pin GPIO4*/
/*SCL pin GPIO5*/
#define SDA 4
#define SCL 5
/*Create the PCF8574 instance*/
/*Set i2c address*/
PCF8574 pcf8574(0x22,SDA,SCL);


void setup()
{
	Serial.begin(115200);
  Serial.println(__FILE__);  //Print file storage path

  pcf8574.pinMode(P4, OUTPUT);
  pcf8574.pinMode(P5, OUTPUT);
  pcf8574.pinMode(P6, OUTPUT);
  //Initialize PCF8574
  pcf8574.begin();
  delay(300);

}

void loop()
{
  pcf8574.digitalWrite(P4, HIGH);
  delay(300);
  pcf8574.digitalWrite(P5, HIGH);
  delay(300);
  pcf8574.digitalWrite(P6, HIGH);
  delay(300);
  pcf8574.digitalWrite(P4, LOW);
  delay(300);
  pcf8574.digitalWrite(P5, LOW);
  delay(300);
  pcf8574.digitalWrite(P6, LOW);
  delay(300);


}
