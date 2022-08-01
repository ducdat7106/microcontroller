//khai báo chân
#define led 2
#define button 23

//khai báo hàm
void Blink_led();
void Read_Button();


void setup()
{
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  pinMode(button, INPUT);
}

void loop()
{
  Blink_led();
  //Read_Button_State();
}

void Blink_led()
{
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

void Read_Button()
{
  Serial.print("Trang thai cua Button: ");
  Serial.println(digitalRead(button));
  
  delay(1000); //1000ms
}
