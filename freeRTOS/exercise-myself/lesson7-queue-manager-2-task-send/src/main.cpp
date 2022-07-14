#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

unsigned int time_handles = 0;

QueueHandle_t xQueue;

void VSend1Task(void *pvParameters);
void VSend2Task(void *pvParameters);

void VReceiveTask(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  xQueue = xQueueCreate(15, sizeof(int));

  if (xQueue == NULL)
    Serial.println("Error create queue");
  else
  {
    Serial.println("Create queue successful");

    // xTaskCreate(VSendTask, "Sender1", 240, (void *)100, 1, NULL);
    // xTaskCreate(VSendTask, "Sender2", 240, (void *)200, 1, NULL);
    xTaskCreate(VSend1Task, "Sender1", 64, NULL, 1, NULL);
    xTaskCreate(VSend2Task, "Sender2", 64, NULL, 1, NULL);

    xTaskCreate(VReceiveTask, "Receiver", 240, NULL, 1, NULL);

    vTaskStartScheduler();
  }

  time_handles = millis();
}

void loop()
{

  if (millis() - time_handles >= 50) // call with period 500 ms
  {
    time_handles = millis();

    Serial.println("infinite loop");
  }
}

void VSend1Task(void *pvParameters)
{
  static unsigned int lValueToSend = 0;

  for (;;)
  {
    xQueueSend(xQueue, &lValueToSend, portMAX_DELAY);
    Serial.print("Sent1 = ");
    Serial.println(lValueToSend);

    lValueToSend++;
    if (lValueToSend >= 1000)
      lValueToSend = 0;

    vTaskDelay(100 / portTICK_PERIOD_MS);

    // taskYIELD();
  }
}

void VSend2Task(void *pvParameters)
{
  static unsigned int lValueToSend1 = 10;

  for (;;)
  {
    xQueueSend(xQueue, &lValueToSend1, portMAX_DELAY);
    Serial.print("Sent2 = ");
    Serial.println(lValueToSend1);

    lValueToSend1++;
    if (lValueToSend1 >= 1000)
      lValueToSend1 = 0;

    vTaskDelay(105 / portTICK_PERIOD_MS);

    // taskYIELD();
  }
}

void VReceiveTask(void *pvParameters)
{
  static unsigned int lReceivedValue1 = 0;
  static unsigned int lReceivedValue2 = 0;

  for (;;)
  {
    if (xQueueReceive(xQueue, &lReceivedValue1, portMAX_DELAY) == pdPASS)
    {
      Serial.print("Received 1 = ");
      Serial.println(lReceivedValue1);
    }

    if (xQueueReceive(xQueue, &lReceivedValue2, portMAX_DELAY) == pdPASS)
    {
      Serial.print("Received 2 = ");
      Serial.println(lReceivedValue2);
    }

    vTaskDelay(110 / portTICK_PERIOD_MS);

    // taskYIELD();
  }
}