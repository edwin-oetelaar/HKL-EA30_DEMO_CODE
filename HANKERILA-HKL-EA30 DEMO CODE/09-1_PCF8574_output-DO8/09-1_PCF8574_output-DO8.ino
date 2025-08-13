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
PCF8574 pcf8574_do8(0x20,SDA,SCL);
void setup()
{
	Serial.begin(115200);
  Serial.println(__FILE__);  //Print file storage path

  pcf8574.pinMode(P4, OUTPUT);
  pcf8574.pinMode(P5, OUTPUT);
  pcf8574.pinMode(P6, OUTPUT);
  pcf8574_do8.pinMode(P0, OUTPUT);
  pcf8574_do8.pinMode(P1, OUTPUT);
  pcf8574_do8.pinMode(P2, OUTPUT);
  pcf8574_do8.pinMode(P3, OUTPUT);
  pcf8574_do8.pinMode(P4, OUTPUT);
  pcf8574_do8.pinMode(P5, OUTPUT);
  pcf8574_do8.pinMode(P6, OUTPUT);
  pcf8574_do8.pinMode(P7, OUTPUT);
  //Initialize PCF8574
  pcf8574.begin();
  pcf8574_do8.begin();
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

  pcf8574_do8.digitalWrite(P0, LOW);
  delay(300);
  pcf8574_do8.digitalWrite(P1, LOW);
  delay(300);
  pcf8574_do8.digitalWrite(P2, LOW);
  delay(300);
  pcf8574_do8.digitalWrite(P3, LOW);
  delay(300);
  pcf8574_do8.digitalWrite(P4, LOW);
  delay(300);
  pcf8574_do8.digitalWrite(P5, LOW);
  delay(300);
  pcf8574_do8.digitalWrite(P6, LOW);
  delay(300);
  pcf8574_do8.digitalWrite(P7, LOW);
  delay(300);

  pcf8574_do8.digitalWrite(P0, HIGH);
  delay(300);
  pcf8574_do8.digitalWrite(P1, HIGH);
  delay(300);
  pcf8574_do8.digitalWrite(P2, HIGH);
  delay(300);
  pcf8574_do8.digitalWrite(P3, HIGH);
  delay(300);
  pcf8574_do8.digitalWrite(P4, HIGH);
  delay(300);
  pcf8574_do8.digitalWrite(P5, HIGH);
  delay(300);
  pcf8574_do8.digitalWrite(P6, HIGH);
  delay(300);
  pcf8574_do8.digitalWrite(P7, HIGH);
  delay(300);


}
