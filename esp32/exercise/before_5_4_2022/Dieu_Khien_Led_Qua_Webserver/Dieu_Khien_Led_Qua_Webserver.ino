//https://vidieukhien.xyz/2020/02/26/lap-trinh-esp32-voi-arduino-web-server-led-control/

#include <WiFi.h>
#include <WebServer.h>

#define LED_PIN GPIO_NUM_2  //2
#define LED_ON HIGH
#define LED_OFF LOW

bool LEDstatus = LED_OFF;

const char* ssidRouter = "Viettel Telecom";
const char* passwordRouter = "dat123456789";

const char *ssidAP = "DEMOESP32AP";
const char *passwordAP = "123456789";

WebServer server(80);

void handleNotFound() 
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  
  for (uint8_t i = 0; i < server.args(); i++) 
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  
  server.send(404, "text/plain", message);
}

String SendHTML(uint8_t ledstart)
{
  int value=15;
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html>\n";
  ptr += "  <head>\n";
  ptr += "    <meta\n";
  ptr += "      name=\"viewport\"\n";
  ptr += "      content=\"width=device-width, initial-scale=1.0, user-scalable=no\"\n";
  ptr += "    />\n";
  ptr += "    <title>LED Control</title>\n";
  ptr += "    <style>\n";
  ptr += "      html {\n";
  ptr += "        font-family: Helvetica;\n";
  ptr += "        display: inline-block;\n";
  ptr += "        margin: 0px auto;\n";
  ptr += "        text-align: center;\n";
  ptr += "      }\n";
  ptr += "      body {\n";
  ptr += "        margin-top: 50px;\n";
  ptr += "      }\n";
  ptr += "      h1 {\n";
  ptr += "        color: #444444;\n";
  ptr += "        margin: 50px auto 30px;\n";
  ptr += "      }\n";
  ptr += "      h3 {\n";
  ptr += "        color: #444444;\n";
  ptr += "        margin-bottom: 50px;\n";
  ptr += "      }\n";
  ptr += "      .button {\n";
  ptr += "        display: block;\n";
  ptr += "        width: 80px;\n";
  ptr += "        background-color: #3498db;\n";
  ptr += "        border: none;\n";
  ptr += "        color: white;\n";
  ptr += "        padding: 13px 30px;\n";
  ptr += "        text-decoration: none;\n";
  ptr += "        font-size: 25px;\n";
  ptr += "        margin: 0px auto 35px;\n";
  ptr += "        cursor: pointer;\n";
  ptr += "        border-radius: 4px;\n";
  ptr += "      }\n";
  ptr += "      .button-on {\n";
  ptr += "        background-color: #3498db;\n";
  ptr += "      }\n";
  ptr += "      .button-on:active {\n";
  ptr += "        background-color: #2980b9;\n";
  ptr += "      }\n";
  ptr += "      .button-off {\n";
  ptr += "        background-color: #34495e;\n";
  ptr += "      }\n";
  ptr += "      .button-off:active {\n";
  ptr += "        background-color: #2c3e50;\n";
  ptr += "      }\n";
  ptr += "      p {\n";
  ptr += "        font-size: 14px;\n";
  ptr += "        color: #888;\n";
  ptr += "        margin-bottom: 10px;\n";
  ptr += "      }\n";
  ptr += "    </style>\n";
  ptr += "  </head>\n";
  ptr += "  <body>\n";
  ptr += "    <h1>ESP32 Web Server</h1>\n";

  if (ledstart)
  {
    ptr += "<p>LED1 Status: ON</p> <a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED1 Status: OFF</p> <a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void handleRoot() 
{
 server.send(200, "text/html", SendHTML(LEDstatus));
}

void setUp_AP_STA_Mode();
void setUp_WiFiRouter_Connect();
void strees_path_when_connect_Basion();
void strees_path_when_connect_Abvanted();

void setup(void) 
{
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT);//Cấu hình GPIO2 là output
  digitalWrite(LED_PIN, LED_OFF);
  
  setUp_AP_STA_Mode();
  
  setUp_WiFiRouter_Connect();

  strees_path_when_connect_Abvanted();

  server.begin();
  Serial.println("\n\nHTTP server started");
}

void loop(void) 
{
  server.handleClient();
  digitalWrite(LED_PIN, LEDstatus);
}

void setUp_AP_STA_Mode()
{
  WiFi.mode(WIFI_AP_STA); //sử dụng đồng thời cả chế độ kết nối tới router wifi và tạo một điểm truy cập cục bộ--> cài đặt chế độ hoạt động của wifi là WIFI_AP_STA
  WiFi.softAP(ssidAP, passwordAP);

  Serial.print("\nWiFi is: ");
  Serial.println(ssidAP);
  
  Serial.print("IP address AP Mode: ");
  Serial.println(WiFi.softAPIP());
}

void setUp_WiFiRouter_Connect()
{
  WiFi.begin(ssidRouter, passwordRouter);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print("... ");
  }
  Serial.print("\nConnected to: ");
  Serial.println(ssidRouter);
  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void strees_path_when_connect_bacsic()
{
  server.on("/", []() {
    server.send(200, "text/plain", "ESP32 Webserver running");
  });

  server.on("/ledon", []() {
    LEDstatus = LED_ON;   //đặt lại giá trị trạng thái LED toàn cầu
    Serial.println("Set LED to ON");    //in các kết quả lên màn hình UART
    server.send(200, "text/plain", "Led ON");   //phản hồi trả về cho Web client
  });

  server.on("/ledoff", []() {
    LEDstatus = LED_OFF;
    Serial.println("Set LED to OFF");
    server.send(200, "text/plain", "Led OFF");
  });

  server.onNotFound(handleNotFound);
}

void strees_path_when_connect_Abvanted()
{
  server.on("/", handleRoot);
  
   server.on("/ledon", []() {
   LEDstatus = LED_ON;
   Serial.println("Set LED to ON");
   server.send(200, "text/html", SendHTML(LEDstatus));
   });
   
   server.on("/ledoff", []() {
   LEDstatus = LED_OFF;
   Serial.println("Set LED to OFF");
   server.send(200, "text/html", SendHTML(LEDstatus));
   });
   
   server.onNotFound(handleNotFound);
}
