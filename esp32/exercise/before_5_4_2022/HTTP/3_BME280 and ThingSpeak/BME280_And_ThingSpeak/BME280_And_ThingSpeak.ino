#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h> //this library needs Adafruit_Sensor.h library 


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

unsigned long delayTime;

//============Funcsion=================
void printValues();

void setup() 
{
  Serial.begin(115200);
  Serial.println(F("BME280 test"));

  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) 
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}

void loop() 
{ 
  printValues();
  delay(delayTime);
}

void printValues() 
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
} 
