#include <stdio.h>
#include <Arduino.h>

// typedef enum StateLed
// {
//   LED_OFF,
//   LED_ON
// };

// StateLed state_led;

typedef struct 
{
  int pin;
  int valueState;
}Led;

Led led1, led2;

void initPin(Led *led, int pins)
{
  led->pin = pins;
}

void printValue(int value)
{
  Serial.println(value);
  delay(1000);
}

void setup() 
{
  // Led led1, led2;
  led1.pin = 22;
  led2.pin = 23;

  // pinMode(led1.pin, OUTPUT);
  // pinMode(led2.pin, OUTPUT);

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);

  Serial.begin(115200);
}

void loop() 
{
  digitalWrite(23, HIGH);
  delay(500);
  digitalWrite(23, LOW);
  delay(500);
}

