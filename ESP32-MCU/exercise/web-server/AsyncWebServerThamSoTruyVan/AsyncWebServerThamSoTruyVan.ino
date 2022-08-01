#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const char* ssid = "Viettel Telecom";
const char* password = "dat123456789";

AsyncWebServer server(80);

void connect_wifi();

void setup()
{
 Serial.begin(115200);
 
 connect_wifi();
 
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
 {
 int paramsNr = request->params();  //số lượng biến có trong request
 
 Serial.println(paramsNr);
 
 for(int i=0;i<paramsNr;i++)
 {
    AsyncWebParameter* p = request->getParam(i);
    
    Serial.print("Param name: ");
    Serial.println(p->name());
    
    Serial.print("Param value: ");
    Serial.println(p->value());
    
    Serial.println("------");
 }
 
 request->send(200, "text/plain", "message received");
 });
 
 server.begin();
}

void loop(){}




void connect_wifi()
{
  WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) 
 {
 delay(1000);
 Serial.println("Connecting to WiFi..");
 }
 Serial.println(WiFi.localIP());
}
