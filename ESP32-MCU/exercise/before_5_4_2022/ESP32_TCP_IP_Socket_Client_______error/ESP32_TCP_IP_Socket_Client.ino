//https://vidieukhien.xyz/2020/02/23/lap-trinh-esp32-voi-arduino-esp32-tcp-ip-socket-client/

/*
ESP32 là một máy khách -->
nó sẽ phải kết nối tới 1 địa chỉ IP qua Wifi. 
--> chế độ WIFI_STA là bắt buộc.
*/

#include <WiFi.h>

const char* ssid = "Viettel Telecom";   //"yourNetworkName";
const char* password =  "dat123456789"; //"yourNetworkPass";

const uint16_t port = 8000;         //cổng lắng nghe
const char * host = "192.168.0.108";//IP của máy chủ 

void setUp_connect_STA_Mode();

void setup()
{

  Serial.begin(115200);

  delay(400);
  setUp_connect_STA_Mode();
}

void loop()
{
  WiFiClient client;

  if (!client.connect(host, port)) 
  {
    Serial.println("Connection to host failed");

    delay(1000);
    return;
  }

  Serial.println("Connected to server successful!");

  client.print("Hello from ESP32!");

  while (client.connected()) 
  {
    while (client.available() > 0) 
    {
      char c = client.read();
      Serial.print(c);  // gửi dữ liệu đến máy chủ +  in các ký tự nhận được lên máy tính qua UART
    }

    delay(10);
  }
  Serial.println();//xuống line for beautyfull
  client.stop();
  Serial.println("Client disconnected");
}

void setUp_connect_STA_Mode()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}
