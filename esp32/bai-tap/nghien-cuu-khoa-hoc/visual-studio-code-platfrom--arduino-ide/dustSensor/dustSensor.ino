#include <Arduino.h>
#include "SharpGP2Y10.h"

//DUST Sensor
int voPin = 34;
int ledPin = 35;
SharpGP2Y10 dustSensor(voPin, ledPin);

void setup() 
{
    Serial.begin(9600);
    pinMode(ledPin,OUTPUT);
}

void loop() 
{
    float dustVal = dustSensor.getDustDensity();
    Serial.println(dustVal);
    Serial.println("error" + String(23) );
    delay(1000);
}
