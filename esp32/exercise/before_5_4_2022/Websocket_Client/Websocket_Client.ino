//https://vidieukhien.xyz/2020/03/06/lap-trinh-esp32-voi-arduino-websocket-client/
#include <WiFi.h>
#include <WebSocketsClient.h>

const char* ssid     = "Viettel Telecom";//"your-ssid";
const char* password = "dat123456789";//"your-password";

WebSocketsClient webSocket;

#define USE_SERIAL Serial

void connect_wifi();

//dữ liệu nhận được là dạng nhị phân ta chuyển đổi sang mã hex
void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) 
{
  const uint8_t* src = (const uint8_t*) mem;
  USE_SERIAL.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for (uint32_t i = 0; i < len; i++) {
    if (i % cols == 0) {
      USE_SERIAL.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    USE_SERIAL.printf("%02X ", *src);
    src++;
  }
  USE_SERIAL.printf("\n");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) 
{
  switch (type) 
  {
    case WStype_DISCONNECTED:
      USE_SERIAL.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);

      // send message to server when Connected
      webSocket.sendTXT("Connected");
      break;
    case WStype_TEXT:
      USE_SERIAL.printf("[WSc] get text: %s\n", payload);

      // send message to server___gửi dữ liệu đến Websocket server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server___gửi dữ liệu dạng chuỗi lên Websocket server (dữ liệu cần gửi ở dạng byte dữ liệu)
      // webSocket.sendBIN(payload, length);
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }

}

void setup() {

  USE_SERIAL.begin(115200);
  
  USE_SERIAL.setDebugOutput(true);
  
  // We start by connecting to a WiFi network
  delay(10);
  connect_wifi();
  
  // server address, port and URL
  webSocket.begin("echo.websocket.org", 80, "/");

  // event handler____xử lý các sự kiện được gửi đến Websocket Client
  webSocket.onEvent(webSocketEvent);


  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);
}

void loop() 
{
  webSocket.loop();
} 

void connect_wifi()
{
  USE_SERIAL.println();  USE_SERIAL.println();//down line for beautyfull
  USE_SERIAL.print("Connecting to ");
  USE_SERIAL.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    USE_SERIAL.print(".");
  }
  
  USE_SERIAL.println("\nWiFi connected");
  USE_SERIAL.print("IP address: ");
  USE_SERIAL.println(WiFi.localIP());
}
