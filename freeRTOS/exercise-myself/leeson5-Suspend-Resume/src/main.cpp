#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

static void MyTask1(void *pvParameters);
static void MyTask2(void *pvParameters);
unsigned int time_handles=0;
void setup()
{
    Serial.begin(9600);
    Serial.println(F("In Setup function"));

    xTaskCreate(MyTask1, "Task1", 64, NULL, 1, &TaskHandle_1);
    xTaskCreate(MyTask2, "Task2", 64, NULL, 2, &TaskHandle_2);
    
    time_handles = millis();
}

void loop()
{
  if(millis()-time_handles >=50)
  {
    Serial.println(F("infinite loop"));
    time_handles = millis();
  }
}

void MyTask1(void *pvParameters)
{
    /* Block for 500ms. */
    const TickType_t  xDelay = 200 / portTICK_PERIOD_MS;

    for (;;)
    {
      static int i=0;
        i++;
        if(i==50)
          i=0;
          
        Serial.println(F("Task1 running"));
        if(i==3)
         vTaskResume(TaskHandle_2);
       
        if(i==30)
          vTaskDelete(NULL);
          
        vTaskDelay(xDelay);
    }
}

static void MyTask2(void *pvParameters)
{
    while (1)
    {
        Serial.println(F("Task 2 running"));
        vTaskSuspend(NULL);
    }
}