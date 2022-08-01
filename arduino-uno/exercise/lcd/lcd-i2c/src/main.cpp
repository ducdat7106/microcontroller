#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int speaker = 7;                 // loa,den ket noi Pin 7
int gas = 6;                    // out ket noi Pin 9
int led = 8;
void setup() {
  pinMode(gas, INPUT);
  pinMode(speaker, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Cam bien Gas:");
}
void loop() {
  if (digitalRead(gas) == HIGH)
  {
    lcd.setCursor(0, 1);
    lcd.print("BAO DONG_WARNING");
    digitalWrite(led, HIGH);
    digitalWrite(speaker, HIGH);
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Binh thuong     ");
    digitalWrite(led, LOW);
    digitalWrite(speaker, LOW);
  }
}