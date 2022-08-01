#include "main.h"
#include "var.h"

int increaseVariable(int value);

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  initConnectWifi();

  route();

  initServer();

  last = millis();
}

void loop()
{
  
}

String readDHTTemperature()
{
  temp = increaseVariable(temp);

  if (temp == 0)
  {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else
  {
    Serial.println(temp);
    return String(temp);
  }
}


String readDHTHumidity()
{
  humi = increaseVariable(humi);

  if (humi == 0)
  {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else
  {
    Serial.println(humi);
    return String(humi);
  }
}

// Replaces placeholder with DHT values
String processor(const String &var)
{
  // Serial.println(var);
  if (var == "TEMPERATURE")
  {
    return readDHTTemperature();
  }
  else if (var == "HUMIDITY")
  {
    return readDHTHumidity();
  }
  return String();
}

int increaseVariable(int value)
{
  int tem = value;
  tem++;
  if (tem > 20)
    tem = 0;
  return tem;
}
