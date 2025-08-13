/*HANKERILA EA30 The first way to read the  digital input */
/*EA30 Digital input code   / install  “PCF8574 library" by Renzo Mischianti*/
#include "Arduino.h"
#include "PCF8574.h"

// Set i2c address
PCF8574 pcf8574(0x22,4,5);  //the address is 0x22  SDA is GPIO4 SCL is GPIO15

/**
 * Setup function
 */
void setup() {
    Serial.begin(115200);  //set the serial port baud rate to 9600
    Serial.println(__FILE__);  //Print the file storage path
    delay(1000);  //Delay for 1000 milliseconds

    pcf8574.pinMode(P0, INPUT);  //Set pin P0 as input
    pcf8574.pinMode(P1, INPUT);  //Set pin P1 as input
    pcf8574.pinMode(P2, INPUT);  //Set pin P2 as input
    pcf8574.pinMode(P3, INPUT);  //Set pin P3 as input

    pcf8574.pinMode(P4, OUTPUT);  //Set pin P0 as input
    pcf8574.pinMode(P5, OUTPUT);  //Set pin P1 as input
    pcf8574.pinMode(P6, OUTPUT);  //Set pin P2 as input
    pcf8574.pinMode(P7, OUTPUT);  //Set pin P3 as input
    pcf8574.begin();  //Start the PCF8574
    pcf8574.digitalWrite(P4,LOW);
    pcf8574.digitalWrite(P5,LOW);
    pcf8574.digitalWrite(P6,LOW);
    pcf8574.digitalWrite(P7,LOW);
}

/**
 * Loop function
 */
void loop() {
     //create a variable to store the value
    uint8_t val1 = pcf8574.digitalRead(P0);  //Read digital value at pin P0
    uint8_t val2 = pcf8574.digitalRead(P1);  //Read digital value at pin P1
    uint8_t val3 = pcf8574.digitalRead(P2);  //Read digital value at pin P2
    uint8_t val4 = pcf8574.digitalRead(P3);  //Read digital value at pin P3


    if (val1==LOW) Serial.println("KEY1 PRESSED");  //If value at P0 is LOW, print "KEY1 PRESSED"
    if (val2==LOW) Serial.println("KEY2 PRESSED");  //If value at P1 is LOW, print "KEY2 PRESSED"
    if (val3==LOW) Serial.println("KEY3 PRESSED");  //If value at P2 is LOW, print "KEY3 PRESSED"
    if (val4==LOW) Serial.println("KEY4 PRESSED");  //If value at P3 is LOW, print "KEY4 PRESSED"


    delay(300);  //Delay for 300 milliseconds
}