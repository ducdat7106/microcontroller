//https://vidieukhien.xyz/2020/02/18/lap-trinh-esp32-voi-arduino-esp32-httpclient-get/


#include <WiFi.h>
#include <HTTPClient.h>// thư viện thực hiện các yêu cầu HTTP GET

const char* ssid = "Viettel Telecom";
const char* password = "dat123456789";

void Connect_WiFi();

void setup() 
{
  Serial.begin(115200);//serial check error
  
  
  Connect_WiFi();
}

void loop() 
{
 //Check the current connection status 
  if ((WiFi.status() == WL_CONNECTED))  
  {
    //khai báo một đối tượng của lớp HTTPClient
    HTTPClient http;   

    /*
      Specify the URL
     
      Câu truy vấn đính kèm vào đường dẫn HTTP request.  /?....
      
      Một biến truy vấn là format với giá trị là json
    */
    http.begin("https://api.ipify.org/?format=json"); 

    //Make the request
    int httpCode = http.GET();                       

    //Check for the returning code
    if (httpCode > 0) 
    {
      //Nhận được phản hồi bằng cách gọi method getString 
      String payload = http.getString();  
      Serial.println(httpCode);
      Serial.println(payload);
    }
    else 
    {
      Serial.println("Error on HTTP request");
    }

    //Free the resources - giải phóng tài nguyên
    http.end(); 
  }
  delay(30000);//30s
}

void Connect_WiFi()
{
  /*
    Duy trì độ trễ trước cuộc gọi WiFi.begin , 
    để đảm bảo rằng mọi thứ được thực hiện trong nền bởi các thư viện đều bắt đầu tốt. 
  */
  delay(100);   
  
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to the WiFi network!!!!!");
  Serial.print("IP: ");
  Serial.println( WiFi.localIP() ); 
}
