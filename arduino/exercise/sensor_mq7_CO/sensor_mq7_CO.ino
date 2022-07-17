const int CO_analog_pin = 34; //GPIO36 CONNECT PIN AD OF ESP32
int CO_Value;

//
//long last=0;
//long timeRead = 1000; //ms
//
//void  ReadSensor();
//double digital_to_ppm(double digital);

void setup() 
{
  //pinMode(CO_analog_pin, INPUT);
  Serial.begin(115200); // khai bao UART , baudrate 115200    
  //Serial.println("Sersor MQ7-AIR CO");
  //last = millis();
}

void loop() 
{
  //ReadSensor();
  CO_Value = analogRead(CO_analog_pin);
  Serial.println( CO_Value );
  delay(1000);
}

//void  ReadSensor()
//{
//  //after time timeRead will read 1st
//  if(millis()-last >= timeRead)
//  {
//    CO_Value = analogRead(CO_analog_pin);  // Doc gia tri adc
//
//    //CO_Value = digital_to_ppm(CO_Value);    
//    Serial.println( CO_Value );
//    
//    last = millis();
//  }
//}
//
//double digital_to_ppm(int digital)
//{
//  /*
//    Dải đo của cảm biến CO: 0-1000ppm  tương đương 0-4096 
//
//    1000     giá trị cần
//
//    4096      digital
//    
//                       (digital*1000)
//    --> giá trị cần = ---------------
//                           4096;
//  */
//  double value=0;
//
//  value = ( (digital*1000)/4096 );
//
//  return value;
//}
