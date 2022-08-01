#define BLYNK_TEMPLATE_ID "TMPLpBdYLvHV"
#define BLYNK_DEVICE_NAME "NCKH BASIC 1"
#define BLYNK_AUTH_TOKEN "dPQne8M3jZdkfnskX2lSF8UMFIq9bIpB"

char auth[] = BLYNK_AUTH_TOKEN;


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
char ssid[] = "TBDK59";
char pass[] = "12345789";

//====Read tín hiệu analog====
#define CO_analog_pin 36

#define nguongCO 100
long CO_Value = 0;
double CO_Value_Change = 0;


//====Time run program
long last=0;
long timeRead = 1000;


//Led on board
#define ledSafeBoard   12 //pin 12 + of Led
#define ledDangerBoard 13 //pin 13 + of Led
#define fanPin  26        //pin 26 connect pin + of Fan( Led)

//Led on app blynk
WidgetLED appledSafeBoard(V2);
WidgetLED appledDangerBoard(V3);
WidgetLCD LCD_Display(V100);


//====Khai báo funcsion child====
void inputOutput();

//Led
void controllLed();
void controllLedOnBoard();
void controllLedOnAppBlynk();

//Fan
void controllFan();

//Lcd App
void writeStringUpLcdBasic();
void writeStringLcdAdvanced();

void  ReadSensor();
//====


void setup()
{
  inputOutput();
  
  Serial.begin(115200); //Init UART

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  
  ReadSensor();
  
  controllLed();
  writeStringLcdAdvanced();
  controllFan();
  
  //Transmit data from esp32 to Blynk App
  Blynk.virtualWrite(V1, CO_Value_Change);
  //Serial.println(CO_Value_Change);
}

void controllLed()
{
  controllLedOnBoard();
  controllLedOnAppBlynk();
}

void controllLedOnBoard()
{
  if(CO_Value_Change<nguongCO)
  {
    digitalWrite(ledSafeBoard, HIGH);
    digitalWrite(ledDangerBoard, LOW);
  }
  else
  {
     digitalWrite(ledSafeBoard, LOW);
     digitalWrite(ledDangerBoard, HIGH);
  }
}

void controllLedOnAppBlynk()
{
   if(CO_Value_Change<nguongCO)
  {
    appledSafeBoard.on();
    appledDangerBoard.off();
  }
  else
  {
     appledSafeBoard.off();
     appledDangerBoard.on();
  }
}

void controllFan()
{
  if(CO_Value_Change<nguongCO)
    digitalWrite(fanPin, LOW);
  else
   digitalWrite(fanPin, HIGH);
}


//No support for web blynk
void writeStringUpLcdBasic()
{
  //lcd on app must setup basic mode
  //transmit data up lcd in app blynk
  Blynk.virtualWrite(V2, "CO_CValue Res: "+ String(CO_Value_Change));   
}

void writeStringLcdAdvanced()
{
  /*
    lcd on app must setup advanced mode
    chi quan tam toi y = 0 or 1
    LCD_Display.print(x, y, CO_Value);
  */
  LCD_Display.print(0, 0, "Nồng độ CO: ");

  if(CO_Value_Change<nguongCO)
  {
    //LCD_Display.print(0, 1, "Safe: "+ String(CO_Value_Change) );
    LCD_Display.print(5, 1, "Safe");
  }
  else
  {
    //LCD_Display.print(0, 1, "Danger: "+ String(CO_Value_Change) );
    LCD_Display.print(5, 1, "Danger");
  }
}

void inputOutput()
{
  //Input
  pinMode(CO_analog_pin, INPUT);

  //Output
  pinMode(ledSafeBoard, OUTPUT);
  pinMode(ledDangerBoard, OUTPUT);
  pinMode(fanPin, OUTPUT);
  digitalWrite(ledSafeBoard, LOW);
  digitalWrite(ledDangerBoard, LOW);
  digitalWrite(fanPin, LOW);
}

void  ReadSensor()
{
  if(millis()-last >= timeRead)
  {
    CO_Value = analogRead(CO_analog_pin); 
    CO_Value_Change = map(CO_Value, 450, 4095, 20, 2000);

    if(CO_Value<450)
      CO_Value=450;

    if(CO_Value_Change<20)
    {
      CO_Value_Change=20;
    }

    Serial.print(CO_Value);
    Serial.print("   ");
    Serial.println(CO_Value_Change);
    
    last = millis();
  }
}
