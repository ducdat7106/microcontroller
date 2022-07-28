#ifndef MAIN_H
#define MAIN_H

#define BLYNK_TEMPLATE_ID "TMPLpBdYLvHV"
#define BLYNK_DEVICE_NAME "NCKH BASIC 1"
#define BLYNK_AUTH_TOKEN "dPQne8M3jZdkfnskX2lSF8UMFIq9bIpB"

#define FIREBASE_HOST "https://tt-iot-utc-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "I8dY6yv4GrCOAASGRfkmOy1nlM4BOrxCT5jCHXWM"

#define reset_system 0

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include <BlynkSimpleEsp32.h>
#include <SharpGP2Y10.h>
#include <FirebaseESP32.h>

typedef enum
{
  LED_TURN_OFF,
  LED_BLINK_1HZ,
  LED_BLINK_10HZ
} Led_State;

typedef enum
{
  Danger,
  Safe 
}Safe_State_Typedef;

typedef struct
{
  int Pin_Sensor, Safe_State, Pin_Led;
  unsigned int Value_Set, Value_Basic, Value_Use;
  unsigned int lowerLimit, upperLimit; //using for map function
} Sensor_Typedef;

typedef struct
{
  Sensor_Typedef Co_Sensor, Gas_Sensor, Dust_Sensor, Sound_Sensor;
  unsigned long time_read;
  Safe_State_Typedef  safe_state_typedef;
} Sensor_Using;



void Init_Hardware();

void Init_Connect_Wifi();
void Current_Connect_Wifi();

void Init_Sensor(Sensor_Using *sensor);
void Get_Value_Set_From_Firebase(Sensor_Using *sensor);
void Set_Data_To_Firebase(Sensor_Using sensor);


void changeTimeReadSensor(Sensor_Using *sensor);
void readSensor(Sensor_Using *sensor);


#endif