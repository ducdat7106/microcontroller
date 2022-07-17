#define BUTTON_PIN 4/* nút nhấn được kết nối với GPIO 4*/

const byte interruptPin = BUTTON_PIN;
volatile int interruptCounter = 0;/* một bộ đếm sẽ được sử dụng báo hiệu rằng một ngắt đã xảy ra*/
int numberOfInterrupts = 0;/* bộ đếm để theo dõi xem có bao nhiêu gián đoạn đã xảy ra trên toàn cầu kể từ khi bắt đầu chương trình.*/

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleInterrupt() {
  portENTER_CRITICAL_ISR(&mux);/*Phần quan trọng cần được bảo vệ khỏi mọi truy cập đồng thời để thay đổi nó*/
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&mux);/*Cho phép tiếp tục chạy các task khác*/
}

void setup() {

  Serial.begin(115200);
  Serial.println("Monitoring interrupts: ");
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

}

void loop() {

  if (interruptCounter > 0) {

    portENTER_CRITICAL(&mux);
    interruptCounter--;
    portEXIT_CRITICAL(&mux);

    numberOfInterrupts++;
    Serial.print("An interrupt has occurred. Total: ");
    Serial.println(numberOfInterrupts);
  }
}
