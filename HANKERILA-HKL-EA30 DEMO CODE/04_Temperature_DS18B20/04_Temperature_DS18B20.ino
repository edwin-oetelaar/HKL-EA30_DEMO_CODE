/*EA30 DS18B20 CODE*/
#include <DS18B20.h>
DS18B20 ds1(15);  //channel-1-DS18b20
DS18B20 ds2(16);  //channel-2-DS18b20
DS18B20 ds3(32);  //channel-3-DS18b20
DS18B20 ds4(33);  //channel-4-DS18b20

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

}
/*DS18B20 temperature detect*/
void loop()
{
  Serial.print("Temperature1:");
  Serial.print(ds1.getTempC());
  Serial.print("℃/\n");
  delay(1000); 
  Serial.print("Temperature2:");
  Serial.print(ds2.getTempC());
  Serial.println(" ℃/\n");
  delay(1000);  
  Serial.print("Temperature3:");
  Serial.print(ds3.getTempC());
  Serial.print("℃/\n");
  delay(1000); 
  Serial.print("Temperature4:");
  Serial.print(ds4.getTempC());
  Serial.println(" ℃/\n");
  delay(1000); 
} 



