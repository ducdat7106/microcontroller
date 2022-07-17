#include <Wire.h> 

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

void setup()
{
  lcd.init();                    
  lcd.backlight();

  //COT 0 1 2 - //HANG 0 1 2 
  lcd.setCursor(0,0);
  lcd.print("NGUYEN DUC DAT");
  
  lcd.setCursor(0,1);
  lcd.print("30-07-2000");
  
  delay(2000);
  lcd.clear();
}

void loop()
{
  lcd.setCursor(5,0);
  lcd.print("IOT DEVELOPER");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(5,1);
  lcd.print("GOOD JOB");
  delay(2000);
  lcd.clear();
  
}
