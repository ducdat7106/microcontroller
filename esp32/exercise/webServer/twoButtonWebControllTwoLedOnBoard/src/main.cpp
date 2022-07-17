#include <Arduino.h>
#include <WiFi.h>

#include <WebServer.h>

#define LED1 27 
#define LED2 26 

// Replace with your network credentials
const char *ssid = "Viettel Telecom";
const char *password = "dat123456789";

// Set web server port number to 80
WebServer myWebServer(80);

//Variable contain code HTLM Website//
const char MainPage[] PROGMEM = R"=====(

  <!DOCTYPE html> 
  <html>
   <head> 
       <title>HOME PAGE</title> 
       <meta charset="UTF-8">
       
       <style> 
          body {
              text-align:left;
            }

          h1 {
              color: blue;
            }
          a {
              text-decoration: none;
              color: white;
            } 

          .button_on {
              height:50px; 
              width:100px; 
              margin:10px 0;
              background-color: red;
              border-radius:5px;
            }

          .button_off {
              height:50px; 
              width:100px; 
              margin:10px 0;
              background-color: green;
              border-radius:5px;
            }

       </style>

      
   </head>

   <body> 

      <h1>ESP32 WebServer</h1> 
      <div>State Led 1: <b>OFF</b> </div>
      <div>
        <button class="button_on"> <a href="/onD1"> ON </a> </button>
        <button class="button_off"> <a href="/offD1">OFF</a> </button>
      </div>

      <div>State Led 2 <b>OFF</b></div>
      <div>
        <button class="button_on"><a href="/onD2">ON</a></button>
        <button class="button_off"><a href="/offD2">OFF</a></button>
      </div>

   </body> 
  </html>
  
)=====";

void initLed();
void initConnectWifi();
void setUpWebServer();

void setup()
{
  Serial.begin(115200);

  initLed();
  
  initConnectWifi();

  setUpWebServer();

  myWebServer.begin();
}

void loop()
{
  //listen client (Web Page)
  myWebServer.handleClient();
}


void initConnectWifi()
{
  WiFi.begin(ssid, password);

  Serial.print("Connecting Wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println(String(ssid)+" have IP");
  Serial.println(WiFi.localIP());
}

void initLed()
{
  //when power for esp32 board, led turn on
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, HIGH); 
  digitalWrite(LED2, HIGH); 
}



void mainPage()
{
  String s = FPSTR(MainPage);
  myWebServer.send(200, "text/html", s);
}

void on_L1()
{
  String s = FPSTR(MainPage);
  digitalWrite(LED1, HIGH);
  myWebServer.send(200, "text/html", s);
}

void off_L1()
{
  String s = FPSTR(MainPage);
  digitalWrite(LED1, LOW);
  myWebServer.send(200, "text/html", s);
}

void on_L2()
{
  String s = FPSTR(MainPage);
  digitalWrite(LED2, HIGH);
  myWebServer.send(200, "text/html", s);
}

void off_L2()
{
  String s = FPSTR(MainPage);
  digitalWrite(LED2, LOW);
  myWebServer.send(200, "text/html", s);
}

void setUpWebServer()
{
  myWebServer.on("/", mainPage);

  myWebServer.on("/onD1", on_L1);
  myWebServer.on("/offD1", off_L1);

  myWebServer.on("/onD2", on_L2);
  myWebServer.on("/offD2", off_L2);
}