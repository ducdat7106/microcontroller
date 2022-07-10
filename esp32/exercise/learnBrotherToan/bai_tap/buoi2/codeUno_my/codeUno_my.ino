#include <ArduinoJson.h>

//khởi tạo uart mềm
#include <SoftwareSerial.h>
const byte RX =2; //nhận
const byte TX =3; //truyền
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

int nhietDo=10;
int doAm = 20;
int dem=30;
float giaTri = 40.40;

long cai1=100;    //lưu trữ dữ liệu
long cai2 = 200;  //lưu trữ dữ liệu

String data_json = "";

long last = 0;//lưu gia trị hàm millis()

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  delay(1000);
  Serial.println("Start UNO!");
  
  last = millis();  //hàm millis()- lưu thời gian hoat động của vi điều khiển
}

void loop() 
{
  //nhận "yêu cầu gửi dữ liệu" từ esp
   read_uart_json();
   
   //gửi dữ kiệu cho esp
   SendData();
}

//truyền dữ liệu JSON tự động
void SendData()
{
   if(millis() - last >= 1000)//1s gửi json 1 lần
  {
    datajson( String(nhietDo), String(doAm), String(dem), String(giaTri) );
    last = millis();
  }
}

void datajson( String nhietDo, String doAm, String dem , String giaTri )
{
  //cấu trúc cơ bản của json
  /*
  {"":"", "":"", "":""}
  
  {"a":"nhietDo","b":"doAm"}
  */

  //tạo chuỗi json
  data_json = "";

  data_json = "{\"ND\":\"" + String(nhietDo) + "\"," + 
              "\"DA\":\"" + String(doAm) + "\"," + 
              "\"D\":\"" + String(dem) + "\"," +
              "\"GT\":\"" + String(giaTri) + "\"}";  

  //kiểm tra xem chuỗi json có đúng không?? ==> để truyền qua esp
  StaticJsonDocument<200> JSON;   //tạo mảng json 200 byte
  DeserializationError  error = deserializeJson(JSON, data_json);
  
  if( error )
  {
    Serial.println("JSON ERROR!!!!!");
    return;
  }
  else
  {
    //hiện thị chuỗi json ra ---> monitor
     Serial.print("Data Json: ");
     serializeJsonPretty(JSON, Serial);   //-->hien thi chuoi json ra monitor
     Serial.println("===============================");  //xuống dòng cho đẹp

     //Truyền dữ liệu qua esp
     serializeJsonPretty(JSON, mySerial);
     mySerial.flush();  //đợi truyền hết tất cả dữ liệu ra cổng uart mềm
     
     JSON.clear();
  }
}

//nhận dữ liệu do esp truyền tới
    //uno nhận
    //esp truyền
void read_uart_json()
{
  /*
  đọc dữ liều board arduino uno truyền tới esp32
  */

  //kiểm tra cổng uart có dữ liệu truyền tới hay không
  while( mySerial.available() )
  {
    //nếu có thì đọc dữ liệu - đọc json    
    const size_t capacity = JSON_OBJECT_SIZE(2)+256;
    DynamicJsonDocument JSON1(capacity);   //DynamicJsonDocument doc(512);  

    DeserializationError  error1 = deserializeJson(JSON1, mySerial);  //kiểm tra lỗi

    if( error1 )
    {
      Serial.println("Data JSON ERROR!");
      return;
    }
    else
    {
       Serial.print("Data JSON ESP: ");
       serializeJsonPretty(JSON1, Serial);    //hiện thị monitor arduino
       Serial.println("================================");  //xuống dòng cho đẹp


       //xử lý dữ liệu nhân được 
              //(dữ liệu send data)
       if(JSON1.containsKey("Send") == 1)//ký tự "Send" phải giống bên esp gửi tới "Send"
       {
          //nếu nhận đúng dc dữ liệu ==> gửi dữ liệu về esp
          datajson( String(nhietDo), String(doAm), String(dem), String(giaTri) );
       }

                //nhận dữ liệu ==> xử lý vấn đề liên quan (dữ liệu ON OFF)
                /*  DIỀU KHIỂN THIẾT BỊ 1
                    {"TB1":"0"}=>OFF
                    {"TB1":"1"}=>ON
                    
                    DIỀU KHIỂN THIẾT BỊ 2
                    {"TB2":"0"}=>OFF
                    {"TB2":"1"}=>ON         */
                    
       else if(JSON1["nhietDo"]=="10")
       {
          //điều khiển cái gì đó
          
          Serial.println("nhiet do on");
          nhietDo = 10; //phải cập nhật giá trị để sau này đồng bộ với web
       }
       else if(JSON1["nhietDo"]=="9")
       {
          Serial.println("nhiet do off");
          nhietDo = 9; //phải cập nhật giá trị để sau này đồng bộ với web
       }
            // lấy dữ liệu ra
            //dữ liệu cài đặt
                //vd hẹn giờ, dimmer... 
        
       else
       {
          if(JSON1.containsKey("C1") == 1)
          {          
             String DataC1 = JSON1["C1"]; //lấy dữ liệu json ra
             cai1 = DataC1.toInt();       //chuyển dữ liệu String về số nguyên
             //cai1 = DataC1.toFloat(); 
             Serial.print("cai1: ");
             Serial.println(cai1);

             //hẹn giờ, dimmer....
          }
          else  if(JSON1.containsKey("C2") == 1)
          {
            String DataC2 = JSON1["C2"];//lấy dữ liệu json ra
            cai2 = DataC2.toInt();//chuyển dữ liệu String về số nguyên
            Serial.print("cai1: ");
            Serial.println(cai2);
          } 
       }
       
       JSON1.clear();
    }
  }
}
