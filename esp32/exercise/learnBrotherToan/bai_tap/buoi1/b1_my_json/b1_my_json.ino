#include <ArduinoJson.h>

int nhietDo=10;
int doAm = 20;
int dem=30;
float giaTri = 40.45;

String data_json = "";//chuoi json

long last = 0;//lưu gia trị hàm millis()

void setup()
{
  Serial.begin(115200);

  delay(1000);
  Serial.println("Start UNO!!!");
   
  last = millis(); //hàm millis()- lưu thời gian hoat động của vi điều khiển
}

void loop() 
{
   Send_Data();
}

//gui du lieu di
void Send_Data()
{
   if(millis() - last >= 1000)//1s gửi json 1 lần
  {
    datajson( String(nhietDo), String(doAm), String(dem), String(giaTri) );
    last = millis();
  }
}

void datajson( String nhietDo, String doAm, String dem , String giaTri )
{
  //cấu trúc của json
  /*
  {"":"", "":"", "":""}
  
  {"a":"nhietDo","b":"doAm"}
  */

  data_json = "";
  data_json = "{\"ND\":\"" + String(nhietDo) + "\"," + 
              "\"DA\":\"" + String(doAm) + "\"," + 
              "\"D\":\"" + String(dem) + "\"," +
              "\"GT\":\"" + String(giaTri) + "\"}";  


  //kiểm tra xem chuỗi json có đúng không?? ==> để truyền qua cho esp
  StaticJsonDocument<200> JSON; //tạo mảng json 200 byte
  DeserializationError  error = deserializeJson(JSON, data_json);

  if( error )
  {
    Serial.println("JSON error!!!");
    return;
  }
  else
  {
    //hiện thị chuỗi json ra monitor
     Serial.print("Data Json: ");
     serializeJsonPretty(JSON, Serial);
     Serial.println("============================");  //xuống dòng cho đẹp
     
     JSON.clear();
  }
}
