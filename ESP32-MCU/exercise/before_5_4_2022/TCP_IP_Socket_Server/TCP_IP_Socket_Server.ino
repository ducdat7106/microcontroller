//https://vidieukhien.xyz/wp-content/uploads/2020/02/2020-02-22-3.png
#include <WiFi.h>
#include <ctype.h>
 
const char* ssid = "Viettel Telecom";//"YourNetworkName";
const char* password =  "dat123456789";//"YourNetworkPassword";
 
WiFiServer wifiServer(80);  //80 là số cổng mà máy chủ sẽ lắng nghe
 
void setUp_connect_wifi();
 
void setup() {
 
  Serial.begin(115200); //kết nối nối tiếp_uart-fix error
 
  delay(1000);
  setUp_connect_wifi();
}
 
void loop() 
{
  WiFiClient client = wifiServer.available();//kiểm tra xem máy khách có kết nối hay không 
 
  if (client) 
  {
    while (client.connected()) //phương thức connected  trả về true nếu máy khách được kết nối 
    {
      while (client.available()>0) 
      {
        char c = client.read();
        client.write(toupper(c));//toupper - chuyển chữ thường thành chữ hoa
      }
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
  }
}

void setUp_connect_wifi()
{
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network!!!\nIP = ");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin(); //chỉ được gọi sau khi đã có địa chỉ IP trong mạng
}
