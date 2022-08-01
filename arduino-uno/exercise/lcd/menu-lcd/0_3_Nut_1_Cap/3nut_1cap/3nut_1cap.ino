
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int len = 4; int gtlen;
int xuong = 5;  int gtxuong;
int menu = 6; int gtmenu;
int demmenu = 0;

void setup() 
{
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
  pinMode(len, INPUT_PULLUP);
  pinMode(xuong, INPUT_PULLUP);
  pinMode(menu, INPUT_PULLUP);
  
  menucapnhat();
}

void loop() 
{
  gtlen = digitalRead(len);
  Serial.print("Lên: "); Serial.print(gtlen); Serial.print("    ");
  gtxuong = digitalRead(xuong);
  Serial.print("Xuống: "); Serial.print(gtxuong); Serial.print("    ");
  gtmenu = digitalRead(menu);
  if (gtlen == 0)
  {
    if (demmenu >= 3)
    { demmenu = 0;  }
    else
    { demmenu++;  }   
    menucapnhat();
    delay(200);
  }
  
  if (gtxuong == 0)
  {
    if (demmenu <= 0)
    { demmenu = 3;  }
    else
    { demmenu--;  }
    menucapnhat();
    delay(200);
  }
  
  if (gtmenu == 0)
  {
    chonmenu();
    menucapnhat();
    delay(200);
  }
  Serial.print("Đếm Menu: "); Serial.print(demmenu); Serial.println("    ");
}

void menucapnhat() 
{
  if (demmenu == 0)
  {
    lcd.clear();
    lcd.print(">MENU 1");
    lcd.setCursor(0, 1);
    lcd.print(" MENU 2");  
  }
  else if (demmenu == 1)
  {
    lcd.clear();
    lcd.print(" MENU 1");
    lcd.setCursor(0, 1);
    lcd.print(">MENU 2");    
  }
  else if (demmenu == 2)
  {
    lcd.clear();
    lcd.print(">MENU 3");
    lcd.setCursor(0, 1);
    lcd.print(" MENU 4");   
  }
  else if (demmenu == 3)
  {
    lcd.clear();
    lcd.print(" MENU 3");
    lcd.setCursor(0, 1);
    lcd.print(">MENU 4");    
  }
}
  
void chonmenu() 
{
  switch (demmenu) 
  {
    case 0:
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MENU 1");
      lcd.setCursor(0,1);
      lcd.print("NOI DUNG MENU 1."); 
      delay(5000);
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MENU 2");
      lcd.setCursor(0,1);
      lcd.print("NOI DUNG MENU 2.");
      delay(5000);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MENU 3");
      lcd.setCursor(0,1);
      lcd.print("NOI DUNG MENU 3.");
      delay(5000);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("MENU 4");
      lcd.setCursor(0,1);
      lcd.print("NOI DUNG MENU 4.");
      delay(5000);
      break;
  }
}
