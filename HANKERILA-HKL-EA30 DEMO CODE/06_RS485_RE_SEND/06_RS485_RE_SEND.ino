//EA30 code of RS485 
/*Send and receive */
void setup() {

  Serial1.begin(115200,SERIAL_8N1,14,13);  //  IO14   485RX   IO13 485TX
  Serial1.println("Welcome to use HANKERILA HKL-EA30"); // RS485 port output the string

}

void loop() {

  /*if Serial2(RS485) receive data ,print it*/
  while(Serial1.available()>0)
   {
    Serial1.print((char)Serial1.read());//Read rs485 receive data  and print it
   }
  delay(200);
}
