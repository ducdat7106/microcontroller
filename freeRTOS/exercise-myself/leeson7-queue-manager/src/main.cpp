#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

unsigned int time_handles = 0;

TaskHandle_t TaskHandle_1;
QueueHandle_t QueueHandle_1;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  QueueHandle_1 = xQueueCreate(10, sizeof(int));

  if (QueueHandle_1 == NULL)
    Serial.println("Error create queue");
  else
    Serial.println("Create successful");

  time_handles = millis();
}

void loop()
{
  // call with period 500 ms
  if (millis() - time_handles >= 500)
  {
    // Serial.println(F("infinite loop"));
    time_handles = millis();
  }
}
