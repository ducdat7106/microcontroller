#define ADCPIN A0

int adcValue;
int value=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ADCPIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   adcValue = analogRead(ADCPIN);

   value = map(adcValue, 450, 4096, 20, 2000);

   if(value<20)
    value=20;

   if(adcValue<460)
    adcValue=460;
   
   Serial.print("have map: ");
   Serial.println(value);
   Serial.println("ko map: "+ String(adcValue));
   
   delay(1000);
}
