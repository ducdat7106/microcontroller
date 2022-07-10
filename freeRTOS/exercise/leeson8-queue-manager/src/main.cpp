#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

uint32_t t_handles = 0;

TaskHandle_t TaskHandle_1 = NULL;
TaskHandle_t TaskHandle_2 = NULL;

QueueHandle_t myQueue;

static void Task1_TX(void *pvParameters);
static void Task2_RX(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  Serial.println("In Setup function");

  xTaskCreate(Task1_TX, "Task1TX", 64, NULL, 2, NULL);
  xTaskCreate(Task2_RX, "Task2RX", 64, NULL, 2, NULL);
}

void loop()
{
  if (millis() - t_handles >= 100)
  {
    t_handles = millis();
    Serial.println("Here infinite loop");
  }
}

static void Task1_TX(void *pvParameters)
{
  char myTxBuff[30];

  myQueue = xQueueCreate(5, sizeof(myTxBuff));
  if (myQueue != NULL)
    Serial.println("Create Queue Successful");
  else
    Serial.println("Error occur when create queue");

  sprintf(myTxBuff, "message 1");
  xQueueSend(myQueue, &myTxBuff, (TickType_t)0);
  Serial.println(myTxBuff);

  sprintf(myTxBuff, "message 2");
  xQueueSend(myQueue, &myTxBuff, (TickType_t)0);
  Serial.println(myTxBuff);

  sprintf(myTxBuff, "message 3");
  xQueueSend(myQueue, &myTxBuff, (TickType_t)0);
  Serial.println(myTxBuff);

  for (;;)
  {
    taskYIELD();
  }
}

static void Task2_RX(void *pvParameters)
{
  char myRxBuffer[30];

  for (;;)
  {
    if (xQueueReceive(myQueue, &myRxBuffer, (TickType_t)10) == pdPASS && myQueue != 0)
    {
      Serial.print("Data received: ");
      Serial.println(myRxBuffer);
    }
    taskYIELD();
  }
}
