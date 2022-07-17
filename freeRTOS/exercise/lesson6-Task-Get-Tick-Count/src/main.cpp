#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

TaskHandle_t TaskHandle_1;

static void MyTask1(void *pvParameters);
unsigned int time_handles = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  xTaskCreate(MyTask1, "Task1", 64, NULL, 1, &TaskHandle_1);

  time_handles = millis();
}

void loop()
{
  // call with period 500 ms
  if (millis() - time_handles >= 100)
  {
    Serial.println(F("infinite loop"));
    time_handles = millis();
  }
}

void MyTask1(void *pvParameters)
{
  /* Block for 500ms. */
  const TickType_t xDelay = 200 / portTICK_PERIOD_MS;

  for (;;)
  {
    static int i = 0;
    TickType_t getTick;

    getTick = xTaskGetTickCount();

    i++;
    if (i == 50)
      i = 0;

    Serial.print(i);
     Serial.print("\t");
    Serial.println(getTick);

    vTaskDelay(xDelay);
    vTaskDelayUntil(&getTick,getTick / portTICK_PERIOD_MS);
  }
}
