/*EA30 OLED SSD1306 display the temperatures */
/*install "U8g2" library*/
/*install "DS18B20" library*/
#include <U8g2lib.h>
#include <Wire.h>
#include <DS18B20.h>
DS18B20 ds1(15);  //channel-1-DS18b20
DS18B20 ds2(16);  //channel-2-DS18b20
DS18B20 ds3(32);  //channel-2-DS18b20
DS18B20 ds4(33);  //channel-2-DS18b20

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,  5, 4, U8X8_PIN_NONE);//SCL IO5  SDA  IO4  
void page1() {

  u8g2.setFont(u8g2_font_timR10_tf);//Font 10
  u8g2.setCursor(0,10);
  u8g2.print("Temp_01:");
  u8g2.print(ds1.getTempC());
  u8g2.print("C");
  u8g2.setCursor(0,25);
  u8g2.print("Temp_02:");
  u8g2.print(ds2.getTempC());
   u8g2.print("C");
   u8g2.setCursor(0,40);
  u8g2.print("Temp_03:");
  u8g2.print(ds3.getTempC());
   u8g2.print("C");
   u8g2.setCursor(0,55);
  u8g2.print("Temp_04:");
  u8g2.print(ds4.getTempC());
   u8g2.print("C");
}
void setup(){
  Serial.begin(9600);
  Serial.println(__FILE__);
  u8g2.setI2CAddress(0x3C*2);
  u8g2.begin();
  u8g2.enableUTF8Print();
}
void loop(){

  u8g2.firstPage();
  do
  {
    page1();
  }while(u8g2.nextPage());

}
