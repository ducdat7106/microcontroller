#include <Arduino.h>

#define led1 23
#define led2 22
#define led3 21
#define ledIdle 19

void initPin();
static void MyTask1(void *pvParameters);
static void MyTask2(void *pvParameters);
static void MyTask3(void *pvParameters);
static void MyTaskIdle(void *pvParameters);


void setup()
{
  initPin();
  Serial.begin(115200);
  Serial.println("Start Program!");
}

void loop()
{
  // Serial.println("run ");
}

void initPin()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(ledIdle, OUTPUT);
  // turn off
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(ledIdle, LOW);

  xTaskCreate(MyTask1, "Task_1", 1024, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task_2", 1024, NULL, 2, NULL);
  xTaskCreate(MyTask3, "Task_3", 1024, NULL, 3, NULL);
  xTaskCreate(MyTaskIdle, "Task_Idle", 1024, NULL,0, NULL);
}

static void MyTask1(void *pvParameters)
{
  for(;;)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(ledIdle, LOW);
    Serial.println("Task1");
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

static void MyTask2(void *pvParameters)
{
  for(;;)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(ledIdle, LOW);
    Serial.println("Task2");
    vTaskDelay(110/portTICK_PERIOD_MS);
  }
}

static void MyTask3(void *pvParameters)
{
  for(;;)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(ledIdle, LOW);
    Serial.println("Task3");
    vTaskDelay(120/portTICK_PERIOD_MS);
  }
}

static void MyTaskIdle(void *pvParameters)
{
  for(;;)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(ledIdle, HIGH);
    Serial.println("Task Idle");
    delay(50);
  }
}

