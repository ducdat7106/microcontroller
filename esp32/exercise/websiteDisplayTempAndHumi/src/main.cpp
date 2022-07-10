#include <Arduino.h>

#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <string>

// HTML & CSS contents which display on web server
String MAIN_page = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - AP Mode &#128522;</h1>\
</body>\
</html>";

const char *ssid = "Viettel Telecom";
const char *password = "dat12345789";

// Set web server port number to 80
WebServer My_WebServer(80);

unsigned int nhietdo = 20, doam = 15;

long last, readTime = 10000;

void printSerult();
void init_ConnectWiFi_Basic();
void init_WebServer();
void ketnoi();
void docdulieunhietdo();
void docdulieudoam();

void setup()
{
  Serial.begin(115200);

  init_ConnectWiFi_Basic();

  init_WebServer();

  last = millis();
}

void loop()
{
  My_WebServer.handleClient(); // hàm thực hiện các yêu cầu từ Client
}


void printSerult()
{
  Serial.println("Nhiet do: " + String(nhietdo) + "  Do am: " + String(doam));

  if (millis() - last >= readTime)
  {
    nhietdo++;
    doam++;
    last = millis();
  }

  if (nhietdo >= 30)
    nhietdo = 20;
  if (doam >= 40)
    doam = 15;
}

void init_ConnectWiFi_Basic()
{
  // khoi tao che do wifi
  WiFi.begin(ssid, password); // bắt đầu kết nối với WiFi

  /*trong chế độ trạm (STA mode) hoặc chế độ điểm truy cập và chế độ trạm đồng thời (AP_STA)*/
  WiFi.mode(WIFI_STA);

  Serial.println("Connecting to WiFi: ");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("... ");
  }

  Serial.println("Connected to the WiFi network !");

  Serial.println("IP: ");
  Serial.println(WiFi.localIP()); // in ra địa chỉ IP của mạng kết nối
}

void init_WebServer()
{
  My_WebServer.on("/", ketnoi);
  My_WebServer.on("/docnhietdo", docdulieunhietdo);
  My_WebServer.on("/docdoam", docdulieudoam);

  My_WebServer.begin();
}

void ketnoi()
{
  String s = MAIN_page;
  My_WebServer.send(200, "text/html", s);
}

void docdulieunhietdo()
{
  nhietdo = 65;
  String snhietdo = String(nhietdo);

  My_WebServer.send(200, "text/plane", snhietdo);
}

void docdulieudoam()
{
  doam = 65;
  String sdoam = String(doam);

  My_WebServer.send(200, "text/plane", sdoam);
}
