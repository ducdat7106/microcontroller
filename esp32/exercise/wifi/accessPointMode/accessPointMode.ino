#include "WiFi.h"

const char *ssid = "ESP32 Access Point Mode";
const char *password = "dat123456789";

int numberDevice=0;

void initConnectWifiAPMode();
int numberDeviceConnect();

void turnOffAccessPointMode();

void setup() 
{
  Serial.begin(115200);
  
  initConnectWifiAPMode();
}

void loop() 
{
    numberDevice = numberDeviceConnect();
    Serial.println("\nNumber Device Connect: "+String(numberDevice));
}

void initConnectWifiAPMode()
{
  /*
  AP Mode : Access Point Mode _ Chế dộ điểm truy cập
  This is mode default of wifi

  ESP32 sẽ như một bộ phát Wifi 
  --> phát ra wifi cho các thiết bị khác bắt.
  */
  WiFi.softAP(ssid, password);
  
  Serial.println("Access Point Mode!!");
  Serial.println( "Name WiFi: " + String(ssid) );
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
}

int numberDeviceConnect()
{
  //Get numbers stations connect to Esp32 in Access Point Mode
  int numbers = WiFi.softAPgetStationNum();

  //Mỗi 2s sẽ kiểm tra 1 lần --> số lượng thiết bị kết nối 
  delay(2000);

  return numbers;
}

void turnOffAccessPointMode()
{
  /*
  disconnects - Ngắt kết nối với wifi 
  
  Set up configuration SSID and password of soft-AP Mode is value null
  Argument wifioff == true --> Turn off soft_AP Mode
  Return true if disconnects Successful
  */
  bool disconnects = WiFi.softAPdisconnect(true);

  if(disconnects == true)
  {
    printf("Successful");
  }
  else if(disconnects == false)
  {
    printf("No successful");
  }
}
