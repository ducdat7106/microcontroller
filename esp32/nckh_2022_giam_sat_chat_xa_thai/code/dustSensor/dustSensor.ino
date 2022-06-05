#include "SharpGP2Y10.h"
 
//DUST Sensor
int voPin = 36;
int ledPin = 32;
float dustDensity = 0;
 
SharpGP2Y10 dustSensor(voPin, ledPin);
 
void setup() {
    Serial.begin(9600);
 
}
 
void loop() {
    dustDensity = dustSensor.getDustDensity();
    Serial.println(dustDensity);
    delay(1000);
}
