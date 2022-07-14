// Time 14-7-2022
// error:  run wrong


#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

unsigned int time_handles = 0;
int value_loop = 111;

const int  number_element_queue = 100;

QueueHandle_t xQueue;

void VSend1Task(void *pvParameters);
void VSend2Task(void *pvParameters);
void VSend3Task(void *pvParameters);

void VReceiveTask(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  xQueue = xQueueCreate(24, sizeof(int));

  if (xQueue == NULL)
    Serial.println("Error create queue");
  else
  {
    Serial.println("Create queue successful");
    Serial.println(value_loop);
    value_loop++;
    if (value_loop >= 65530)
      value_loop = 0;

    // xTaskCreate(VSendTask, "Sender1", 240, (void *)100, 1, NULL);
    // xTaskCreate(VSendTask, "Sender2", 240, (void *)200, 1, NULL);
    xTaskCreate(VSend1Task, "Sender1", 64, NULL, 4, NULL);
    xTaskCreate(VSend2Task, "Sender2", 64, NULL, 3, NULL);
    xTaskCreate(VSend3Task, "Sender3", 64, NULL, 2, NULL);

    xTaskCreate(VReceiveTask, "Receiver", 240, NULL, 1, NULL);

    vTaskStartScheduler();
  }

  time_handles = millis();
}

void loop()
{

  if (millis() - time_handles >= 200) // call with period 500 ms
  {
    Serial.println("infinite loop");
    
    time_handles = millis();
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

    vTaskDelay(110 / portTICK_PERIOD_MS);

    // taskYIELD();
  }
}

void VSend3Task(void *pvParameters)
{
  static unsigned int lValueToSend2 = 20;

  for (;;)
  {
    xQueueSend(xQueue, &lValueToSend2, portMAX_DELAY);
    Serial.print("Sent3 = ");
    Serial.println(lValueToSend2);

    lValueToSend2++;
    if (lValueToSend2 >= 1000)
      lValueToSend2 = 0;

    vTaskDelay(120 / portTICK_PERIOD_MS);

    // taskYIELD();
  }
}

void VReceiveTask(void *pvParameters)
{
  static unsigned int lReceivedValue[4];

  for (;;)
  {
    if (xQueueReceive(xQueue, &lReceivedValue[0], portMAX_DELAY) == pdPASS &&
        xQueueReceive(xQueue, &lReceivedValue[1], portMAX_DELAY) == pdPASS &&
        xQueueReceive(xQueue, &lReceivedValue[2], portMAX_DELAY) == pdPASS)
    {
      Serial.print("Received 1 = ");
      Serial.println(lReceivedValue[0]);

      Serial.print("Received 2 = ");
      Serial.println(lReceivedValue[1]);

      Serial.print("Received 3 = ");
      Serial.println(lReceivedValue[2]);
    }

    vTaskDelay(130 / portTICK_PERIOD_MS);

    // taskYIELD();
  }
}