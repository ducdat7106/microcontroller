//https://vidieukhien.xyz/2020/02/29/lap-trinh-esp32-voi-arduino-asynchronous-http-web-server/

#include "WiFi.h"
#include "ESPAsyncWebServer.h"  //thư viện máy chủ web HTTP không đồng bộ
 
const char* ssid = "Viettel Telecom";
const char* password =  "dat123456789";

//thiết lập máy chủ HTTP ESP32 không đồng bộ
AsyncWebServer server(80);  

void connect_wifi();

void setup()
{
  Serial.begin(115200);

  connect_wifi();

  // Lambda body implementation
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request)  
  {
    request->send(200, "text/plain", "Hello World");
  });
 
  server.begin();
}
 
void loop()
{
  
}

void connect_wifi()
{
  WiFi.begin(ssid, password);

 Serial.println("Connecting to WiFi...  Waite");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }
  
  Serial.println("Connecting to WiFi: ");
  Serial.print(WiFi.localIP());   // IP cục bộ
  Serial.print("/hello");
}
