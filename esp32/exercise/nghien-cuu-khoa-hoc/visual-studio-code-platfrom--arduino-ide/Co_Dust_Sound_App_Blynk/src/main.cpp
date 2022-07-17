#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPLpBdYLvHV"
#define BLYNK_DEVICE_NAME "NCKH BASIC 1"
#define BLYNK_AUTH_TOKEN "dPQne8M3jZdkfnskX2lSF8UMFIq9bIpB"
char auth[] = BLYNK_AUTH_TOKEN;

#define FIREBASE_HOST "https://tt-iot-utc-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "I8dY6yv4GrCOAASGRfkmOy1nlM4BOrxCT5jCHXWM"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SharpGP2Y10.h>
#include <FirebaseESP32.h>

const char ssid[] = "Viettel Telecom";
const char pass[] = "dat123456789";

#define CO_Pin 36
#define CO_Value_Set 100
unsigned int CO_Value_Basic = 0;
unsigned int CO_Value_Use = 0;

#define GAS_Pin 39
#define GAS_Value_Set 700
unsigned int GAS_Value_Basic = 0;
unsigned int GAS_Value_Use = 0;

#define SOUND_Pin 32
#define SOUND_Value_Set 3800
unsigned int SOUND_Value_Basic = 0;
unsigned int SOUND_Value_Use = 0;

#define DUST_Pin 34     // pin Vo
#define DUST_Led_Pin 35 // pin led+
#define DUST_Value_Set 1100
unsigned int DUST_Value_Basic = 0;
unsigned int DUST_Value_Use = 0;

bool CO_Safe;
bool Gas_Safe;
bool Sound_Safe;
bool Dust_Safe;

unsigned int maxAnalog = 4096;
unsigned int minAnalog = 0;

// Led on board
#define ledSafeBoard 22   // pin 12 + of Led
#define ledDangerBoard 23 // pin 13 + of Led

// Led on app blynk
WidgetLED COAppLedSafe(V2);
WidgetLED COAppLedDanger(V3);

WidgetLED SOUNDAppLedSafe(V12);
WidgetLED SOUNDAppLedDanger(V13);

WidgetLED DUSTAppLedSafe(V22);
WidgetLED DUSTAppLedDanger(V23);

WidgetLED GASAppLedSafe(V42);
WidgetLED GASAppLedDanger(V43);

WidgetLCD LCDs(V100);


unsigned int lastTime;
unsigned int outTime = 1000; // 1000ms



void initPin();

void checkSafe();
void controllDisplay();
void controllLedBoard();
void controllLedApp();
void writeLcdBa();
void writeLcdAd();

void readCo();
void readDust();
void readSound();

void runBlynks();
void readSenser();

SharpGP2Y10 dustSensor(DUST_Pin, DUST_Led_Pin);

FirebaseData fbdata;

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  Serial.println("Connect wifi " + String(ssid) + " success.");

  initPin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  lastTime = millis(); 

}

void loop()
{
  runBlynks();

  readSenser();

  controllDisplay();

  Firebase.setInt(fbdata, "Node1/co", CO_Value_Use);
  Firebase.setInt(fbdata, "Node1/dust", DUST_Value_Use);
  Firebase.setInt(fbdata, "Node1/sound", SOUND_Value_Use);
  Firebase.setInt(fbdata, "Node1/gas", GAS_Value_Use);

}

void readSenser()
{
  if (millis() - lastTime >= outTime)
  {
    readCo();
    readDust();
    readSound();

    lastTime = millis();
  }
}

void runBlynks()
{
  Blynk.run();

  // Transmit data from esp32 to Blynk App
  Blynk.virtualWrite(V1, CO_Value_Use);
  Blynk.virtualWrite(V11, SOUND_Value_Use);
  Blynk.virtualWrite(V21, DUST_Value_Use);
}

void controllDisplay()
{
  checkSafe();

  controllLedBoard();
  controllLedApp();
  writeLcdAd();
}

void checkSafe()
{
  if (CO_Value_Use <= CO_Value_Set)
    CO_Safe = 1;
  else
    CO_Safe = 0;

  if (DUST_Value_Use <= DUST_Value_Set)
    Dust_Safe = 1;
  else
    Dust_Safe = 0;

  if (SOUND_Value_Use <= SOUND_Value_Set)
    Sound_Safe = 1;
  else
    Sound_Safe = 0;
  
  if (GAS_Value_Use <= GAS_Value_Set)
    Gas_Safe = 1;
  else
    Gas_Safe = 0;

}

void controllLedBoard()
{
  if (CO_Safe && Dust_Safe && Sound_Safe && Gas_Safe)
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

void controllLedApp()
{
  if (CO_Safe)
  {
    COAppLedSafe.on();
    COAppLedDanger.off();
  }
  else
  {
    COAppLedSafe.off();
    COAppLedDanger.on();
  }

  if (Sound_Safe)
  {
    SOUNDAppLedSafe.on();
    SOUNDAppLedDanger.off();
  }
  else
  {
    SOUNDAppLedSafe.off();
    SOUNDAppLedDanger.on();
  }

  if (Dust_Safe)
  {
    DUSTAppLedSafe.on();
    DUSTAppLedDanger.off();
  }
  else
  {
    DUSTAppLedSafe.off();
    DUSTAppLedDanger.on();
  }

  
  if (Gas_Safe)
  {
    GASAppLedSafe.on();
    GASAppLedDanger.off();
  }
  else
  {
    GASAppLedSafe.off();
    GASAppLedDanger.on();
  }

}

// No support for web blynk
void writeLcdBa()
{
  /*
  Ba - Basic
  transmit data up lcd in app blynk
  lcd on app must setup basic mode
  */

  Blynk.virtualWrite(V100, "CO_CValue Res: " + String(CO_Value_Use));
}

void writeLcdAd()
{
  /*
  Ad - Advanced
  lcd on app must setup advanced mode
  */

  static int counter;

  LCDs.print(0, 0, "environment:");

  if (CO_Safe && Dust_Safe && Sound_Safe && Gas_Safe)
  {
    LCDs.print(5, 1, "safe");
    counter++;
  }
  else
  {
    LCDs.print(5, 1, "danger");
  }

  if (counter % 4 == 0)
  {
    LCDs.clear();
  }
}

void initPin()
{
  // Input
  pinMode(CO_Pin, INPUT);
  pinMode(DUST_Pin, INPUT);
  pinMode(SOUND_Pin, INPUT);
  pinMode(GAS_Pin, INPUT);


  // Output
  pinMode(ledSafeBoard, OUTPUT);
  pinMode(ledDangerBoard, OUTPUT);
  digitalWrite(ledSafeBoard, LOW);
  digitalWrite(ledDangerBoard, LOW);
}

void readCo()
{
  unsigned int lowerLimit = 20;
  unsigned int upperLimit = 900;

  CO_Value_Basic = analogRead(CO_Pin);
  CO_Value_Use = map(CO_Value_Basic, minAnalog, maxAnalog, lowerLimit, upperLimit);

  Serial.println("\n\nCO Gas value basic: " + String(CO_Value_Basic) + "  CO Gas value use: " + String(CO_Value_Use));
}

void readGas()
{
  unsigned int lowerLimit = 200;
  unsigned int upperLimit = 2000;

  GAS_Value_Basic = analogRead(CO_Pin);

  GAS_Value_Use = map(CO_Value_Basic, minAnalog, maxAnalog, lowerLimit, upperLimit);

  Serial.println("\n\nCO Gas value basic: " + String(CO_Value_Basic) + "  CO Gas value use: " + String(CO_Value_Use));
}

void readSound()
{
  unsigned int lowerLimit = 3000;
  unsigned int upperLimit = 4000;

  SOUND_Value_Basic = analogRead(SOUND_Pin);
  SOUND_Value_Use = map(SOUND_Value_Basic, minAnalog, maxAnalog, lowerLimit, upperLimit);

  Serial.println("Sound value basic: " + String(SOUND_Value_Basic) + "  Dust value use: " + String(SOUND_Value_Use));
}

void readDust()
{
  unsigned int lowerLimit = 1000;
  unsigned int upperLimit = 3000;

  DUST_Value_Basic = dustSensor.getDustDensity();
  DUST_Value_Use = map(DUST_Value_Basic, minAnalog, maxAnalog, lowerLimit, upperLimit);

  Serial.println("Dust value basic: " + String(DUST_Value_Basic) + "  Dust value use: " + String(DUST_Value_Use));
}