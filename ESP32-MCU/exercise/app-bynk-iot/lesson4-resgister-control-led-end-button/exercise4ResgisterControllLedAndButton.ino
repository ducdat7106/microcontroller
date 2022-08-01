/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLH2i3GFwl"
#define BLYNK_DEVICE_NAME "Measure Resgister And Controll Led"
#define BLYNK_AUTH_TOKEN "ZHy34p5VoyJ7rM1kg8DMrxCYGSlXrVfV"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;


// Your WiFi credentials.   // Set password to "" for open networks.
char ssid[] = "Viettel Telecom";
char pass[] = "dat123456789";


//POT-HG
#define pot_hg1   34
#define pot_hg2   35

int value1 = 0;//value resgister
int value2 = 0;//value resgister

//app button 
int appButton1;
int appNutton2;

//button on testboard
#define button1 39//no press -->connect +5V
int statusButton=0;


//led on board
#define led1 12
#define led2 13
#define led3 26
#define led4 27

//led on app blynk
WidgetLED appLed1(V20);
WidgetLED appLed2(V21);
WidgetLED appLed3(V22);
WidgetLED appLed4(V23);
WidgetLED appLed5(V24);
WidgetLED appLed6(V25);

#define nguong1 2000
#define nguong2 2000

//==================App Button================================

//chieu truyen du lieu: tu Blynk xuong esp32
BLYNK_WRITE(V10)//read button
{
  appButton1 = param.asInt();//read status button
  
  if(appButton1 == 1)
  {
    digitalWrite(led4, HIGH);//dieu khien led tren esp32
    appLed4.on();//dieu khien led tren app Blynk
  }
  else
  {
    digitalWrite(led4, LOW);
    appLed4.off();//dieu khien led tren app Blynk
  }
}
//=========================================================

//==================Button phyrical========================
/*gay ra lỗi trên blynk: đơ. phản hồi quá chậm*/
//void button_testboard()
//{
//  if(digitalRead(button1) == 0)
//  {
//    while( !digitalRead(button1) );
//    statusButton++;
//  }
//
//  if(statusButton>1)
//    statusButton = 0;
//
//  if(statusButton ==1 )
//    digitalWrite(led4, HIGH);//dieu khien led tren esp32
//  else
//    digitalWrite(led4, LOW);//dieu khien led tren esp32
//}

//=========================================================
void setup()
{
  Serial.begin(115200); //INIT UART
  Blynk.begin(auth, ssid, pass);

  //==============NO define pin input================
  //pinMode(analogPin, INPUT);//pin input
  //==============NO define pin input================

   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);
   pinMode(led4, OUTPUT);

   digitalWrite(led1, LOW);
   digitalWrite(led2, LOW);
   digitalWrite(led3, LOW);
   digitalWrite(led4, LOW);

   pinMode(button1, INPUT); 
}

void loop()
{
  Blynk.run();

  value1 = analogRead(pot_hg1);
  value2 = analogRead(pot_hg2);

  //button_testboard();
  
  controllLed();

  
  //transmit data from esp32 to Blynk App
  Blynk.virtualWrite(V0, value1);
  Blynk.virtualWrite(V1, value2);
  
  Serial.print(value1);  Serial.print("   ");
  Serial.println(value2);
}

void controllLed()
{
  if(value1 == 0)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    appLed1.off();
    appLed2.off();
    appLed3.off();
  }
  else if(value1<nguong1)
  {
     digitalWrite(led1, HIGH);
     digitalWrite(led2, LOW);
     digitalWrite(led3, LOW);
     appLed1.on();
     appLed2.off();
     appLed3.off();
  }
  else if(value1<nguong1+1000 && value1>=nguong1)
  {
     digitalWrite(led1, LOW);
     digitalWrite(led2, HIGH);
     digitalWrite(led3, LOW);
     appLed1.off();
     appLed2.on();
     appLed3.off();
  }
  else
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
     appLed1.off();
     appLed2.off();
     
     digitalWrite(led3, HIGH);
     appLed3.on();
     delay(1000);
     digitalWrite(led3, LOW);
     appLed3.off();
     delay(1000);
  }
}
