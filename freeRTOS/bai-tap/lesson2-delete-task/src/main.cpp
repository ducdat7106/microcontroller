#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

#define led1 12
#define led2 10

TaskHandle_t TaskHandle_1 = NULL;
TaskHandle_t TaskHandle_2 = NULL;

void initPin();

void MyTask1(void *pvParameters);
void MyTask2(void *pvParameters);
void MyTaskIdle(void *pvParameters);

void setup()
{
  Serial.begin(9600);

  initPin();

  xTaskCreate(MyTask1, "LED1", 64, NULL, 1, &TaskHandle_1);
  xTaskCreate(MyTaskIdel, "Idle", 64, NULL, 0, NULL);

  vTaskStartScheduler();

  Serial.println("Start program");
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
    static int digit = 0;
    digit++;
    if (digit == 10)
      digit = 0;

    Serial.println("Task1 running");

    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    if (digit == 1)
      xTaskCreate(MyTask2, "LED2", 64, NULL, 2, &TaskHandle_2);

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void MyTask2(void *pvParameters)
{
  for (;;)
  {
     static int digit = 0;
    digit++;
    if (digit == 10)
      digit = 2;
    Serial.println("Task2 is running and about to delete ifself");

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    
    if (digit ==1 )
      vTaskDelete(TaskHandle_1); // vTaskDelete(NULL);

    vTaskDelay(110 / portTICK_PERIOD_MS);
  }
}

void MyTaskIdel(void *pvParameters)
{
  for (;;)
  {
    Serial.println("Task Idle running");

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    vTaskDelay(40 / portTICK_PERIOD_MS);
  }
}