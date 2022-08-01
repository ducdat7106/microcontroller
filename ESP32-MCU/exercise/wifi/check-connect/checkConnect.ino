//https://vidieukhien.xyz/2020/02/17/lap-trinh-esp32-voi-arduino-esp32-ket-noi-mang-wifi/

/*thư viện wifi*/
#include "WiFi.h"

/*thông tin đăng nhập mạng*/
/*tên mạng*/
/*mật khẩu*/
const char* ssid = "Viettel Telecom";   
const char* password =  "dat123456789"; 

void initConnectWifi();

void setup() 
{
  //init uart
  Serial.begin(115200);
  
  initConnectWifi();
}

void loop()
{
  //do nothing
}

void initConnectWifi()
{
  //khoi tao che do wifi
  //bắt đầu kết nối với WiFi 
  WiFi.begin(ssid, password);
  
  /*trong chế độ trạm (STA mode) hoặc chế độ điểm truy cập và chế độ trạm đồng thời (AP_STA)*/
  WiFi.mode(WIFI_STA);  
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to the WiFi network: " + String(ssid));
  
  //in ra address IP của network connect
  Serial.print("IP:\t\t\t");
  Serial.println(WiFi.localIP() );  
}
