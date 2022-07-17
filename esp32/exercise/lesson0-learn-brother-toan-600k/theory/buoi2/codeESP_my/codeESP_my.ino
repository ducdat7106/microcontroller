#include <ArduinoJson.h>//6.10.0

//thiết lập uart mềm
#include <SoftwareSerial.h>//2.5.0
const byte RX = D5;  //nhận    pin 3 uno
const byte TX = D6;  //truyền  pin 2 uno
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

long last = 0;

String DataSend = "";

void setup()
{
  Serial.begin(9600);   //dùng để fix eror
  mySerial.begin(9600);  //sử dụng để nhận dữ liệu từ arduino uno

  delay(1000);
  Serial.println("\nStart ESP!!!");

  last = millis();
}

void loop() 
{
  //gửi "yêu cầu truyền dữ liệu"
  Send_Commend(); 

  //nhận dữ liệu do Uno gửi tới
  read_uart_json();
}

//nhận dữ liệu
//đọc dữ liệu từ board arduino uno truyền tới esp32
    //uno truyền
    //esp nhận
void read_uart_json()
{
  //kiểm tra cổng uart có dữ liệu truyền tới hay không
  while(mySerial.available())
  {
    //ko có dữ liệu ==> ko làm gì cả
    
    //nếu có ==> đọc dữ liệu ==> đọc JSON
    
    const size_t capacity = JSON_OBJECT_SIZE(2)+256;//khai báo mảng JSON
    DynamicJsonDocument JSON(capacity);     

    DeserializationError  error = deserializeJson(JSON, mySerial);  //kiểm tra lỗi dữ liệu

    if( error )
    {
      Serial.println("Data JSON error!!!!!");
      return;
    }
    else
    {
       Serial.print("Data json UNO: ");
       serializeJsonPretty(JSON, Serial);//hiện thị monitor arduino
       Serial.println("====================");  //xuống dòng cho đẹp

       
       // XỬ LÝ VÀ ĐƯA DỮ LIỆU LÊN SERVER 

       
       JSON.clear();  //xóa mảng dữ liệu
    }
  }
}

 //gửi lệnh
     //esp truyền
     //uno nhận
void Send_Commend()
{
  if(millis()-last >=3000)//3s 1 lần gửi
  {
    //JSON {"Send":"1"}
    DataSend = "";
    DataSend = "{\"Send\":\"1\"}";

  
    StaticJsonDocument<200> JSON1;//tạo mảng json 200 byte
    DeserializationError  error1 = deserializeJson(JSON1, DataSend);
  
    if( error1 )
    {
      Serial.println("JSON error!!!");
      return;
    }
    else
    {
      //Truyền dữ liệu từ esp đén uno
       Serial.println("\nDa gui lenh"); 
       serializeJsonPretty(JSON1, mySerial);
       mySerial.flush();//đợi truyền hết dữ liệu ra cổng uart mềm
       
       JSON1.clear();
    }
    
    last = millis();
  } 
}
