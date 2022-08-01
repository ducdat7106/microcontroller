#include <ESP8266WiFi.h>

const char *ssid = "duc dat";
const char *password = "ducdat123";

unsigned long currentMillis = 0;  //hien tai
unsigned long previousMillis = 0; //truoc
unsigned long interval = 1e4; //khoang thoi gian   //10s

int led = 2;

void connect_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //WiFi.begin(ssid);
  Serial.println("Connecting wifi");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void reconnect_wifi_after_lost_connect()
{
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}

void do_work()
{
  switch(WiFi.status())
  {
    case WL_NO_SSID_AVAIL:
      Serial.println("No find wifi");
      digitalWrite(led, HIGH);
      break;
    case WL_CONNECTED:
      Serial.println("Connect wifi successful");
      digitalWrite(led, LOW);
      break;
    case WL_CONNECT_FAILED:
      Serial.println("connect error");
      break;
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  connect_wifi();

  reconnect_wifi_after_lost_connect();
}

void loop()
{
  currentMillis = millis();
  if(currentMillis - previousMillis > interval)
  {
     do_work();
     previousMillis = currentMillis;
  }
}
