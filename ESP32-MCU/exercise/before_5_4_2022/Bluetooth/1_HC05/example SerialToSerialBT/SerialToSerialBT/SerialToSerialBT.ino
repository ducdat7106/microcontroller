#include "BluetoothSerial.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial objec
BluetoothSerial SerialBT;

const int led = 4;  //LED is connected to GPIO4
const int temp_sensor = 14;     //ds18b20 is connected to GPIO14

OneWire oneWire(temp_sensor); //oneWire object created
DallasTemperature sensors(&oneWire); 


String message = "";
char incomingChar;
String temperature = "";


unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 20000;        // interval at which to publish sensor readings
                                    //20000 minis


void setup() {
  pinMode(led, OUTPUT);//Specifying led as output
  Serial.begin(115200);
  SerialBT.begin("MCU_ESP32S"); //Bluetooth device name
  Serial.println("Start pairing!");
}

void loop() {
  unsigned long currentMillis = millis();
  // Send temperature readings
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    sensors.requestTemperatures(); 
    temperature = String(sensors.getTempCByIndex(0)) + "C  " +  String(sensors.getTempFByIndex(0)) + "F";
    SerialBT.println(temperature); 
  }
  
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  
  if (message =="on"){
    digitalWrite(led, HIGH);
  }
  else if (message =="off"){
    digitalWrite(led, LOW);
  }
  delay(20);
}
