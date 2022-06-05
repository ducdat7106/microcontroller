#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "web.h"
ESP8266WebServer MyServer(80);


#include <ArduinoJson.h>
#include <SoftwareSerial.h>//2.5.0
const byte RX = D5;  //nhận
const byte TX = D6;  //truyền 
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

long last = 0;
String DataSend = "";


const char* ssid = "dat";   /*tên mạng*/
const char* password =  "ducdat12a1"; /*mật khẩu*/


void SendWebPage();
void DK_Den();
void DK_Quat();

void setup() 
{
  Serial.begin(115200);//uart
  
  ConnectWiFi();  //connect wifi
  
  last = millis();
  
  //show web
  MyServer.on("/", []{
    SendWebPage();
  });

  
  //show web
  MyServer.on("/onclickden", []{
    DK_Den();
  });
  

  //show web
   MyServer.on("/onclickquat", []{
    DK_Quat();
  });


  
  //begin server
  MyServer.begin();
  Serial.println("Server Start!!");
}

void loop()
{
  //duy trì server
  MyServer.handleClient();

  sendCommend();//gửi lệnh
  read_uart_json();
}


void ConnectWiFi()
{
   WiFi.begin(ssid, password);
   Serial.println("Connected....");

   while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected WiFi!");

  Serial.println("IP of ESP: ");
  Serial.println(WiFi.localIP() );
}

void SendWebPage()
{
  //cập nhật lại giao điện web 
  MyServer.send(200, "text/html", webpage_my);

  /*
  + 200 Send ok
  + "text/html" : thuộc tính HTML
  + webpage_my : mảng dữ liệu
  */
}

void DK_Den()
{
  //kiểm tra xem esp đã phản ứng chưa
  Serial.println("den da bat!");
  
  //cập nhật lại giao điện web 
  MyServer.send(200, "text/html", webpage_my);
}


void DK_Quat()
{
  Serial.println("quat da chay!");

  //cập nhật lại giao điện web 
  MyServer.send(200, "text/html", webpage_my);
}

void read_uart_json()
{
  /*
  đọc dữ liều board arduino uno truyền tới esp32
  */

  //kiểm tra cổng uart có dữ liêuj truyền tới hay không
  while(mySerial.available())
  {
    //nếu có thì đọc dữ liệu
    //đọc json
    
    const size_t capacity = JSON_OBJECT_SIZE(2)+256;
    DynamicJsonDocument JSON(capacity);   //DynamicJsonDocument doc(512);  

    DeserializationError  error = deserializeJson(JSON, mySerial);  //kiểm tra lỗi

    if( error ) //(error == true)
    {
      Serial.println("Data JSON error");
      return;
    }
    else
    {
       Serial.print("Data json UNO OK: ");
       serializeJsonPretty(JSON, Serial);//hiện thị monitor arduino
       Serial.println("====================");  //xuống dòng cho đẹp


       
       JSON.clear();
    }
  }
}


void sendCommend()
{
  if(millis()-last >=3000)
  {
    //JSON {"Send":"1"}
    DataSend = "";
    DataSend = "{\"Send\":\"1\"}";

    StaticJsonDocument<200> JSON1;//tạo mảng json 200 byte
  
  
  DeserializationError  error1 = deserializeJson(JSON1, DataSend);

  if( error1 ) //(error == true)
  {
    Serial.println("JSON error!!!");
    return;
  }
  else
  {
     Serial.println("Da gui lenh"); 
    //Truyền dữ liệu qua esp
     serializeJsonPretty(JSON1, mySerial);
     mySerial.flush();//đợi truyền hết dữ liệu ra cổng uart mềm
     
     JSON1.clear();
  }
 }
}
