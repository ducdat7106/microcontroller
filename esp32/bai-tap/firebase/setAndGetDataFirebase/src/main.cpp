#include <Arduino.h>

// library already exist
#include <WiFi.h>
#include <WiFiClient.h>

// must download add
#include <FirebaseESP32.h>

#define WIFI_SSID "Viettel Telecom"
#define WIFI_PASSWORD "dat123456789"

#define FIREBASE_HOST "https://tt-iot-utc-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "I8dY6yv4GrCOAASGRfkmOy1nlM4BOrxCT5jCHXWM"

FirebaseData fbdata;

typedef struct
{
  unsigned int set_1, set_2, get_1, get_2;
} Firebase_Typedef;

void initSetNumber(Firebase_Typedef *setNumber);
void increaseNumber(Firebase_Typedef *value);
void initWifi();
void getDataNumberFromFirebase(Firebase_Typedef *valueGet);
void firebase_Handle(Firebase_Typedef *data5base);
void result_handle(Firebase_Typedef result);

Firebase_Typedef value_Temperature;

void setup()
{
  Serial.begin(115200);

  initWifi();

  initSetNumber(&value_Temperature);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  firebase_Handle(&value_Temperature);

  result_handle(value_Temperature);
}

void initSetNumber(Firebase_Typedef *setNumber)
{
  setNumber->set_1 = 3;
  setNumber->set_2 = 7;
}

void increaseNumber(Firebase_Typedef *value)
{
  (value->set_1)++;
  if ((value->set_1) >= 20)
    value->set_1 = 0;

  (value->set_2)++;
  if ((value->set_2) >= 15)
    value->set_2 = 0;
}

void initWifi()
{
  delay(1000);

  Serial.print("Connecting to: " + String(WIFI_SSID));
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("\nWiFi connected successful.\nIP address: ");
  Serial.println(WiFi.localIP());
}

void getDataNumberFromFirebase(Firebase_Typedef *valueGet)
{
  valueGet->get_1 = Firebase.getInt(fbdata, "Node3/a1");
  if (valueGet->get_1)
    valueGet->get_1 = fbdata.to<int>();

  valueGet->get_2 = Firebase.getInt(fbdata, "Node3/a2");
  if (valueGet->get_2)
    valueGet->get_2 = fbdata.to<int>();
}

void firebase_Handle(Firebase_Typedef *data5)
{
  static unsigned long time_handle = 0, flags = 0;

  if (millis() - time_handle >= 1000) // each 1s handle once
  {
    increaseNumber(data5);

    time_handle = millis();

    flags = 1;
  }

  if (flags == 1)
  {
    // set number
    Firebase.setInt(fbdata, "Node1/Temp", data5->set_1);
    Firebase.setInt(fbdata, "Node1/Humi", data5->set_2);

    // set string
    Firebase.setString(fbdata, "Node2/Athod1 ", "Nguyen Duc Dat " + String(data5->set_1));
    Firebase.setString(fbdata, "Node2/Athod2 ", "Dang Thi Nhien " + String(data5->set_2));

    // get data from firebase
    getDataNumberFromFirebase(data5);

    flags = 0;
  }
}

void result_handle(Firebase_Typedef result)
{
  Serial.print("\n\n\nResult: ");
  Serial.print("\nData set: " + String(result.set_1) + "\t" + String(result.set_2));
  Serial.print("\nData get: " + String(result.get_1) + "\t" + String(result.get_2));
}
