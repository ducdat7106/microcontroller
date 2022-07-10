#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>

// Import required libraries
#include "wifi/mywifi.h"
#include "web/myWebServer.h"

String readDHTTemperature();
String readDHTHumidity();
String processor(const String& var);

void increaseVariable();

#endif