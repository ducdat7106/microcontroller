#include <Arduino.h>

#include<WiFi.h>
#include<WebServer.h>
#include<string>

#define LED 2

// Replace with your network credentials
const char* ssid = "Viettel Telecom";
const char* password = "dat123456789";

// Set web server port number to 80
WebServer myWebServer(80);

void initConnectWifi();
void Create_Button();


void setup() 
{
  Serial.begin(115200);

  //when power for esp32 board, led will in state turn off 
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  initConnectWifi();

  Create_Button();
  
   myWebServer.begin();
}

void loop() 
{
  //lắng nghe truy vấn từ trình duyệt web
  myWebServer.handleClient();
}


void initConnectWifi()
{
  //delay 1s to set up system
  delay(1000);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  Serial.print("Start connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Wifi "+String(ssid)+"\nIP:\t");
  Serial.println(WiFi.localIP());
}


void Create_Button()
{
  /*
  my_WebServer.on("/toggle"....

  đường dẫn trên web--> /toggle
 */

 /*
  code create button on webserver
  "<button><a href=\"/toggle\">TOGGLE</a></button>";

  Muốn viết dấu " trong dấu " " --> phía trước dấu " phải có dấu \
  -->"......\".....\".........."
 */

  myWebServer.on("/", [](){ 

    myWebServer.send(200, "text/html", "<button><a href=\"/toggle\">TOGGLE</a></button>");

  });
  
  myWebServer.on("/toggle", [](){

    digitalWrite(LED, !digitalRead(LED));//read button

    myWebServer.send(200, "text/html", "<button><a href=\"/toggle\">TOGGLE</a></button>"); 
    
  });
}
