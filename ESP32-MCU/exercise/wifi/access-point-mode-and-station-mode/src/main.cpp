#include <Arduino.h>
#include<WiFi.h>

//==============Name WiFi And Pasword Of Access Point==================== 
const char *ssid_ap = "myEsp32";
const char *passwd_ap = "dat123456789";

IPAddress local_IP_ap(192,168,4,9);//can change
IPAddress gateway_ap(192,168,4,9);
IPAddress subnet_ap(255,255,255,0);

//=================Station Infomation==================
const char *ssid_sta = "Viettel Telecom";
const char *passwd_sta = "dat123456789";

void setup()
{
  //Setup Access Point Mode And Station Mode
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  //==============================================


  //Access Point Mode
  WiFi.softAPConfig(local_IP_ap, gateway_ap, subnet_ap);
  WiFi.softAP(ssid_ap, passwd_ap);
  //==================================================

  //Station Mode
  WiFi.begin(ssid_sta, passwd_sta);
  //=============================================

  //Setup port serial and print IP connected at Station Mode 
  Serial.begin(9600);
  Serial.print("Conecting");

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("...");
  }
  Serial.println(WiFi.localIP() );

}

void loop() 
{

}