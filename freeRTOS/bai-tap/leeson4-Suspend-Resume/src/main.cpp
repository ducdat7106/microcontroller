#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

static void MyTask1(void *pvParameters);
static void MyTask2(void *pvParameters);

void setup()
{
    Serial.begin(9600);
    Serial.println(F("In Setup function"));

    xTaskCreate(MyTask1, "Task1", 64, NULL, 1, &TaskHandle_1);
    xTaskCreate(MyTask2, "Task2", 64, NULL, 2, &TaskHandle_2);
}

void loop()
{
    Serial.println(F("infinite loop"));
    delay(10);
}

void MyTask1(void *pvParameters)
{
    for (;;)
    {
        Serial.println(F("Task1 Suspend itself"));
        vTaskSuspend(NULL);

        Serial.println(F("Task1 running again"));
    }
}

static void MyTask2(void *pvParameters)
{
    while (1)
    {
        static int value = 0;
        value++;
        if (value == 20)
            value = 1;
        if (value == 19)
        {
            Serial.println(F("Task2 Resume Task1"));
            vTaskResume(TaskHandle_1);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
