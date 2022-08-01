/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLKobMAatn"
#define BLYNK_DEVICE_NAME "LearnLed"
#define BLYNK_AUTH_TOKEN "1-ILJHei_Ifx5ngtq_gA64PQ1l5M5IRP"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
char ssid[] = "Viettel Telecom";
char pass[] = "dat123456789";

//Bien
#define led1 12
#define led2 13
#define led3 14

int button1;
int button2;
int button3;

//Led on App Blynk
WidgetLED ledRapp(V4);
WidgetLED ledYapp(V5);
WidgetLED ledBapp(V6);

/*
  Read button
 
  BLYNK_WRITE connect giua esp32 with  App Blynk
  V1 la chan ao duoc thiet lap trong App Blynk
  Chieu truyen du lieu: tu Blynk xuong esp32
*/
BLYNK_WRITE(V1)
{
  //Read status button
  button1 = param.asInt();
  
  if(button1 == 1)
  { 
    //Controll led on esp32 board
    digitalWrite(led1, HIGH);

    //Controll led on App Blynk
    ledRapp.on();
  }
  else
  {
    digitalWrite(led1, LOW);
    ledRapp.off();
  }
}

BLYNK_WRITE(V2)
{
  button2 = param.asInt();
  
  if(button2 == 1)
  {
    digitalWrite(led2, HIGH);
    ledYapp.on();
  }
  else
  {
    digitalWrite(led2, LOW);
    ledYapp.off();
  }
}

BLYNK_WRITE(V3)
{
  button3 = param.asInt();
  
  if(button3 == 1)
  {
    digitalWrite(led3, HIGH);
    ledBapp.on();
  }
  else
  {
    digitalWrite(led3, LOW);
    ledBapp.off();
  }
}

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  //when power chip, led will turn off
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop()
{
  Blynk.run();
}
