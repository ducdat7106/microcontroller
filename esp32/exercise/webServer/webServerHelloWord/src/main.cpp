/*
Tutorial:

https://vidieukhien.xyz/2020/02/24/lap-trinh-esp32-voi-arduino-esp32-webserver/


Explain function:

https://github.com/espressif/arduino-esp32/blob/cfe8526ec8bf1c899f78d610051f6ab79ef022d7/libraries/WebServer/src/WebServer.h#L120
*/

#include <Arduino.h>

/*
  Sử dụng thư viện WiFi.h để:
    +Kết nối với wifi và
    +Tạo điểm truy cập wifi mềm Soft AP
*/
#include <WiFi.h>

/*
  Thư viện WebServer.h phục vụ cho việc:
    +Tạo máy chủ web và
    +Xử lý các giao thức HTTP

*/
#include <WebServer.h>

// Thông tin kết nối wifi (Router)
const char *ssid = "Viettel Telecom";
const char *password = "dat123456789";

// Cấu hình Soft AP
const char *ssidAP = "ESP32 AP Mode";
const char *passwordAP = "dat123456789";

/*
 Khai báo một đối tượng của thư viện WebServer.h
    +80 là cổng mặc định cho HTTP
*/
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

void initAP_STA_Mode();
void pathConnect();

void setup(void)
{
  Serial.begin(115200);

  initAP_STA_Mode();

  pathConnect();
  /*
    Bắt đầu chạy máy chủ web

    Node: chỉ được gọi sau khi đã có địa chỉ IP trong mạng.
  */
  server.begin();

  Serial.println("\n\nHTTP server started");
}

void loop(void)
{

  // Handling incoming client requests
  server.handleClient();
}

void initAP_STA_Mode()
{
  /*
   Sử dụng đồng thời cả:
     +Chế độ kết nối tới router wifi và
     +Tạo một điểm truy cập cục bộ
   --> cài đặt chế độ hoạt động của wifi là WIFI_AP_STA
  */
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssidAP, passwordAP);
  //Serial.println(WiFi.softAPIP());
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void pathConnect()
{
  /*
    Đối đầu vào là các hàm xử lý sự kiện.

    server.send : web server trả lời web clienta4
  */

  //Đường dẫn gốc: -->"/"
  server.on("/", []()
            { server.send(200, "text/plain", "ESP32 Webserver running"); });

  //Đường dẫn cụ thể-->"/hi"
  server.on("/hi", []()
            { server.send(200, "text/plain", "Hello Word. I am Dat. I live in Bac Ninh."); });

  //Đường dẫn chưa xử lý-->hàm chức năng onNotFound --/abc
  server.onNotFound(handleNotFound);
}
