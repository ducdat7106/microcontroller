#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // initialize the LCD
	lcd.begin();

  // lcd.backlight();
  lcd.noBacklight();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("lcd 16x02");
}

void loop()
{
  // put your main code here, to run repeatedly:
}