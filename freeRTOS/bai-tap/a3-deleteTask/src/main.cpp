#include <Arduino.h>
// #include "freertos/task.h"

// #include "FreeRTOSConfig.h"


#define led1 23
#define led2 22

TaskHandle_t TaskHandle_2;

void initPin();
void MyTask1(void *pvParameters);
void MyTask2(void *pvParameters);


void setup()
{
  Serial.begin(115200);
  initPin();
  xTaskCreate(MyTask1, "LED1", 1024, NULL, 1, NULL);
  vTaskStartScheduler();
  Serial.println("start program");
}

void loop()
{


}

void initPin()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void MyTask1(void *pvParameters)
{
  while (1)
  {
    Serial.println("Task1 running");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    xTaskCreate(MyTask2, "LED2", 1024, NULL, 2, &TaskHandle_2);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void MyTask2(void *pvParameters)
{
  Serial.println("Task2 is running and about to delete ifself");
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  vTaskDelete(TaskHandle_2);
}