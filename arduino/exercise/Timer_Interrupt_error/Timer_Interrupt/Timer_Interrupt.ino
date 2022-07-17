// Stop button is attached to PIN 0 (IO0)
#define BTN_STOP_ALARM    4

volatile int interruptCounter;
int totalInterruptCounter;  /* bộ đếm bổ sung để theo dõi có bao nhiêu gián đoạn đã xảy ra kể từ khi bắt đầu chương trình. */

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() 
{
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);

}

void setup() {

  Serial.begin(115200);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);

}

void loop() {

  if (interruptCounter > 0) {

    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);

    totalInterruptCounter++;

    Serial.print("An interrupt as occurred. Total number: ");
    Serial.println(totalInterruptCounter);

  }
  // If button is pressed
  if (digitalRead(BTN_STOP_ALARM) == LOW) 
  {
    // If timer is still running
    Serial.println("Button Pressed, Stop Timer");
    if (timer) 
    {
      // Stop and free timer
      timerEnd(timer);
      
      timer = NULL;
    }
  }
}
