/*
  If value resgister big than 500 --> turn on led
*/
/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLpBdYLvHV"
#define BLYNK_DEVICE_NAME "NCKH BASIC 1"
#define BLYNK_AUTH_TOKEN "dPQne8M3jZdkfnskX2lSF8UMFIq9bIpB"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.   
char ssid[] = "Viettel Telecom";
char pass[] = "dat123456789";

#define resgistorPin 35
int valueResgister;

//Led on board
#define ledBoardSafe   12
#define ledBoardDanger 13

//led on app blynk
WidgetLED ledAppSafe(V11);
WidgetLED ledAppDanger(V12);
WidgetLCD Lcds(V2);

void resgister_control_led();

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  
  pinMode(resgistorPin, INPUT);
  
  pinMode(ledBoardSafe, OUTPUT);
  pinMode(ledBoardDanger, OUTPUT);
  digitalWrite(ledBoardSafe, LOW);
  digitalWrite(ledBoardDanger, LOW);
}

void loop()
{
  Blynk.run();
  
  valueResgister = analogRead(resgistorPin);

  resgister_control_led();

  //write_String_lcd_basic();
  write_String_lcd_advanced();
  
  //transmit data from esp32 to Blynk App
  Blynk.virtualWrite(V1, valueResgister);
  Serial.println(valueResgister);
}


void resgister_control_led()
{
  if(valueResgister<1000)
  {
    digitalWrite(ledBoardSafe, HIGH);
    ledAppSafe.on();

     digitalWrite(ledBoardDanger, LOW);
    ledAppDanger.off();   
  }
  else
  {
    digitalWrite(ledBoardSafe, LOW);
    ledAppSafe.off();

    digitalWrite(ledBoardDanger, HIGH);
     ledAppDanger.on();
  }
}


//no support for web blynk
void write_String_lcd_basic()
{
  //lcd on app must setup basic mode
  ////transmit data to lcd in app blynk
  Blynk.virtualWrite(V2, "value Res: "+ String(valueResgister));
  
}

//no support for web blynk
void write_String_lcd_advanced()
{
  //lcd on app must setup advanced mode

  Lcds.print(0, 0, "CO: ");
  
  if(valueResgister<1000)
    Lcds.print(0, 1, "Safe: "+ String(valueResgister) );
  else
    Lcds.print(0, 1, "Danger: "+ String(valueResgister) );
  
}
