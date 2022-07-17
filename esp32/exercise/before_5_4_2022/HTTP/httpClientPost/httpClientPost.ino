//https://vidieukhien.xyz/2020/02/19/lap-trinh-esp32-voi-arduino-esp32-httpclient-post/
/*
  POST được sử dụng để gửi dữ liệu đến máy chủ để tạo / cập nhật tài nguyên.
*/
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Viettel Telecom";
const char* password =  "dat123456789";

void Connect_WiFi();

void setup() 
{
  Serial.begin(115200);

   
  Connect_WiFi();
}

void loop() 
{
  if ((WiFi.status() == WL_CONNECTED))  //Check the current connection status
  {
    HTTPClient http;//khai báo một đối tượng của lớp HTTPClient

    http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
    
    http.addHeader("Content-Type", "text/plain");             //Specify content-type header,  text/plain 
  
    int httpResponseCode = http.POST("POSTING from ESP32");   //Send the actual POST request
 
    if( httpResponseCode>0 )  // Nếu yêu cầu  được gửi thành công
    {
    String response = http.getString();   //Get the response to the request_chuyển qua làm nội dung chính của yêu cầu
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
   }
   else
   {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
   }

    http.end(); //Free the resources
  }
  delay(30000);
}

void Connect_WiFi()
{
  //Delay needed before calling the WiFi.begin
  delay(4000);  
  
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP() ); 
}
