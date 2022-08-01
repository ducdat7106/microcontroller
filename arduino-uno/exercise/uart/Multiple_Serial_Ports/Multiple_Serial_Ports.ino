#include <HardwareSerial.h>
/*
uart2 
tx GPIO17
rx GPIO16
*/
char buff[50];  //buffer
volatile byte indx=0; //index

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200);
}
  
void loop() 
{
  //using Hercules để mô phỏng
  while (Serial2.available()>0 ) 
  {
    byte c = Serial2.read();
    Serial2.write( char(c) );

    if(indx<sizeof buff)
    {
      buff[indx++] = c;// save data in the next index in the array buff
      if(c == '\r')//check for the end of the word
      {
        Serial.println(buff);
        indx= 0; //reset button to zero
      }
    }
    
  }
}


/*
THAM KHẢO TẠI:
https://deviot.vn/tutorials/esp32.66047996/esp32-uart.38331059

https://diyi0t.com/uart-tutorial-for-arduino-and-esp8266/
*/
