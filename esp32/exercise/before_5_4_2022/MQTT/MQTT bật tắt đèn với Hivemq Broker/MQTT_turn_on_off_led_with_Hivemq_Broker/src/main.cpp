#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>

#define BUT1 4
#define BUT2 16
#define LED1 17
#define LED2 5
String ledStatus1 = "ON";
String ledStatus2 = "ON";

//Information wifi
const char* ssid = "Viettel Telecom";
const char* password = "dat123456789";
 
//===Information MQTT Broker====
//Server broker và port lấy trên hivemq
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883 //Port của CloudMQTT

// user and password 
#define MQTT_USER "esp32_1"
#define MQTT_PASSWORD "ducdat12a1"
 
//Create 2 topic save value của Led1 and Led2
#define MQTT_LED1_TOPIC "MQTT_ESP32/LED1"
#define MQTT_LED2_TOPIC "MQTT_ESP32/LED2"
#define MQTT_LED2_DEMO "MQTT_ESP32/DEMO"
 
unsigned long previousMillis = 0; 
const long interval = 5000;
 
WiFiClient wifiClient;
PubSubClient client(wifiClient);
 
 //Funcsion connect wifi
void setup_wifi() 
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 

void connect_to_broker() 
{
  /*
    Connect with broker

    After connect, will sub with 2 topic LED1 and LED2 để receiver data from Broker về.
  */

 //wait to when have connect
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");//Attempting - cố gắng

    String clientId = "ESP32";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");
      client.subscribe(MQTT_LED1_TOPIC);
      client.subscribe(MQTT_LED2_TOPIC);
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}
 
void callback(char* topic, byte *payload, unsigned int length) 
{
  /*
    Funcsion callback để receiver data

    Mỗi khi có dữ liệu thay đổi trên broker, 
    hàm callback sẽ được gọi. 
    
    Ở đây sử lý như sau:
    + Copy dữ liệu trả về (payload) và status
    + Kiểm tra đó là topic nào
    + Ghi trạng thái led với dữ liệu trả về tương ứng với mỗi topic
  */
  char status[20];

  Serial.println("-------new message from broker-----");
  
  Serial.print("Message arrived topic: ");
  Serial.println(topic);

  Serial.print("message: ");
  Serial.write(payload, length);
  Serial.println();

  for(int i = 0; i<length; i++)
  {
    status[i] = payload[i];
  }

  Serial.println(status);

  if(String(topic) == MQTT_LED1_TOPIC)
  {
    if(String(status) == "OFF")
    {
      ledStatus1 = "OFF";
      digitalWrite(LED1, LOW);
      Serial.println("LED1 OFF");
    }
    else if(String(status) == "ON")
    {
      ledStatus1 = "ON";
      digitalWrite(LED1, HIGH);
      Serial.println("LED1 ON");
    }
  }
 
  if(String(topic) == MQTT_LED2_TOPIC)
  {
    if(String(status) == "OFF")
    {
      ledStatus2 = "OFF";
      digitalWrite(LED2, LOW);
      Serial.println("LED2 OFF");
    }
    else if(String(status) == "ON")
    {
      ledStatus2 = "ON";
      digitalWrite(LED2, HIGH);
      Serial.println("LED2 ON");
    }
  }
   
}

void Publish_du_lieu_len_MQTT()
{
  /*
    Mỗi khi nhấn nút, sẽ kiểm tra trạng thái của ledstatus, 
    sau đó đảo ngược trạng thái đó.
    Tiếp tới dùng client.publish để đẩy dữ liệu đó lên broker.
  */
  if(digitalRead(BUT1) == 0) 
  {
    while (digitalRead(BUT1) == 0)
    {
      /* cho nut dc nha */
    }

    if(ledStatus1 == "ON")
    {
      client.publish(MQTT_LED1_TOPIC, "OFF"); // Khi kết nối sẽ publish thông báo
      ledStatus1 = "OFF";
    }
    else if(ledStatus1 == "OFF")
    {
      client.publish(MQTT_LED1_TOPIC, "ON");
      ledStatus1 = "ON";
    }
  }

  if(digitalRead(BUT2) == 0) 
  {
    while (digitalRead(BUT2) == 0)
    {
      /* cho nut dc nha */
    }
    if(ledStatus2 == "ON")
    {
      client.publish(MQTT_LED2_TOPIC, "OFF");
      ledStatus2 = "OFF";
    }
    else if(ledStatus2 == "OFF")
    {
      client.publish(MQTT_LED2_TOPIC, "ON");
       ledStatus2 = "ON";
    }
  }
}
 
void setup() 
{
  Serial.begin(9600);

  Serial.setTimeout(500);
  setup_wifi();

  client.setServer(MQTT_SERVER, MQTT_PORT );

  client.setCallback(callback);///Subcrible dữ liêu từ MQTT

  connect_to_broker();

  Serial.println("Start transfer");
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}
 
  
void loop() 
{
  client.loop();

  //test connect
  if (!client.connected()) 
  {
    connect_to_broker();
  }
 
  Publish_du_lieu_len_MQTT();
  
}

void print_string()
{
  /*
    after mỗi 2s will thực hiện publish line "hello world" lên  MQTT Brocker
  */
  long lastMsg = 0;
  char msg[50];
  int value = 0;

  long now = millis();

  if (now - lastMsg > 2000) 
  {
    lastMsg = now;
    ++value;

    snprintf (msg, 75, "hello world #%ld", value);

    Serial.print("Publish message: ");
    Serial.println(msg);
    
    client.publish(MQTT_LED2_DEMO, msg);
  }
}


/*
https://khuenguyencreator.com/lap-trinh-esp32-mqtt-bat-tat-den-voi-hivemq-broker/



*/