#include <Arduino.h>

#include <FirebaseESP32.h>
#include <WiFi.h>
#include <WiFiClient.h>

#define FIREBASE_HOST "https://tt-iot-utc-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "I8dY6yv4GrCOAASGRfkmOy1nlM4BOrxCT5jCHXWM"

FirebaseData fbdata;

#define WIFI_SSID "Viettel Telecom"
#define WIFI_PASSWORD "dat123456789"

unsigned int x, y;
unsigned int results, result1, result2;
long last, timeSet = 1000;

int increaseNumber(int value);
void initWifi();
int getDataFrom5Base(const char * c);

void setup()
{
  x = 0;
  y=23;

  last = millis();

  Serial.begin(115200);

  initWifi();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  if (millis() - last >= timeSet)
  {
    x = increaseNumber(x);
    y = increaseNumber(y);

    Serial.println("x = " + String(x) + " y = " + String(y));

    last = millis();
  }

  Firebase.setInt(fbdata, "Node1/Temp", x);
  Firebase.setInt(fbdata, "Node1/Humi", y);

  Firebase.setString(fbdata, "Node2/Athod1 ", "Nguyen Duc Dat " + String(x + 10));
  Firebase.setString(fbdata, "Node2/Athod2 ", "Dang Thi Nhien " + String(y + 20));

  result1 = getDataFrom5Base("Node3");
  Serial.println("Get Data Firebase = " + String(result1));

  result2 = getDataFrom5Base("Node4");
  Serial.println("Get Data Firebase = " + String(result2));

  delay(500);
}

int increaseNumber(int value)
{
  value++;
  if(value>100)
    value=0;
  return value;
}

void initWifi()
{
  delay(1000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Dang ket noi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Da ket noi WiFi!");
  Serial.println(WiFi.localIP());
}

int getDataFrom5Base(const char * c)
{
  int results, result1s;

  results = Firebase.getInt(fbdata, c);
  if(results)
  {
    result1s = fbdata.to<int>();
  }

  return result1s;
}