#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

void Task1(void *pvParameters);
void Task2(void *pvParameters);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

void setup()
{
    Serial.begin(9600);

    xTaskCreate(Task1, "LED1", 64, NULL, 3, &TaskHandle_1);
    xTaskCreate(Task2, "LED2", 64, NULL, 2, &TaskHandle_2);

    vTaskStartScheduler();

    delay(1000);
}

void loop()
{

}

void Task1(void *pvParameters)
{
    UBaseType_t uxPriority = uxTaskPriorityGet(NULL);
    while (1)
    {
        Serial.println("\nTask 1 is running and about to raise Task2 Priority");
        vTaskPrioritySet(TaskHandle_2, (uxPriority + 1));
    }
}

void Task2(void* pvParameters)
{
    UBaseType_t uxPriority = uxTaskPriorityGet(NULL);
    while(1)
    {
        Serial.println("Task 2 is running and about to lower Task 2 Priority\n");
        vTaskPrioritySet(TaskHandle_2, (uxPriority-2));
    }
}