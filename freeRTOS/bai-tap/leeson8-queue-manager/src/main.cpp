#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

TaskHandle_t TaskHandle_1;

QueueHandle_t queue;

void setup()
{
  Serial.begin(9600);
  Serial.println("In Setup function");

  queue = xQueueCreate(10, sizeof(int));
}

void loop()
{
  if (queue == NULL)
  {
    Serial.println("Error create queue");
    return;
  }
  else
    Serial.println("Create successful");

  for (int i = 0; i < 5; i++)
  {
    xQueueSend(queue, &i, 0);
  }

  int element;
  for (int i = 0; i < 5; i++)
  {
    Serial.println("---------------------------------");
    xQueueReceive(queue, &element, 0);
    int messagesWaiting = uxQueueMessagesWaiting(queue);
    int emptySpaces = uxQueueSpacesAvailable(queue);

    Serial.println("Number element in queue: ");
    Serial.println(messagesWaiting);
    Serial.println("Space: ");
    Serial.println(emptySpaces);
  }

  Serial.println();
  delay(1000);
}
