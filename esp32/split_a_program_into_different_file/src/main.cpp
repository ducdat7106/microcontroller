#include <Arduino.h>

#include "firebase1.h"
#include "wifis.h"

extern int x1s;

void setup()
{
  Serial.begin(115200);

  initConnectWifi();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  x1s=15;
  setFirebase();
  getFirebase();
}