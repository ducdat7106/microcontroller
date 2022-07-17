#include <ESP8266WiFi.h>

const char *ssid = "duc dat";
const char *password = "ducdat123";

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println("Connect Wifi successful!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println("Disconnected Wifi!");
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  //WiFi.begin(ssid);  //wifi have not password
}

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

void setup()
{
  Serial.begin(115200);

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  connect_wifi();
}

void loop()
{
  
}
