/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLpBdYLvHV"
#define BLYNK_DEVICE_NAME "resgister comtrol led"
#define BLYNK_AUTH_TOKEN "dPQne8M3jZdkfnskX2lSF8UMFIq9bIpB"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.   // Set password to "" for open networks.
char ssid[] = "Viettel Telecom";
char pass[] = "dat123456789";

#define analogPin 35
int value;

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  pinMode(analogPin, INPUT);
}

void loop()
{
  value = analogRead(analogPin);
  Serial.println(value);
   
  //transmit data from esp32 to Blynk App
  Blynk.run();
  Blynk.virtualWrite(V1, value);
}
