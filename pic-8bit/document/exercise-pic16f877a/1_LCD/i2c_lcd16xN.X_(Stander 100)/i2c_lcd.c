#include "I2C_LCD.h"
 
unsigned char RS, i2c_add, BackLight_State = LCD_BACKLIGHT;
 
//LCD module with I2C address = 0x4E
void LCD_Init(unsigned char I2C_Add, unsigned char I2C_BaudRate)
{
    I2C_Master_Init(I2C_BaudRate);
    __delay_ms(100);
    
    i2c_add = I2C_Add;
    IO_Expander_Write(0x00);
    __delay_ms(30);
    LCD_Cmd(0x03);
    __delay_ms(5);
    LCD_Cmd(0x03);
    __delay_ms(5);
    LCD_Cmd(0x03);
    __delay_ms(5);
    LCD_Cmd(LCD_RETURN_HOME);
    __delay_ms(5);
    LCD_Cmd(0x20 | (LCD_TYPE << 2));
    __delay_ms(50);
    LCD_Cmd(LCD_TURN_ON);
    __delay_ms(50);
    LCD_Cmd(LCD_CLEAR);
    __delay_ms(50);
    LCD_Cmd(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
    __delay_ms(50);
}
 
void IO_Expander_Write(unsigned char Data)
{
  I2C_Master_Start();
  I2C_Master_Write(i2c_add);
  I2C_Master_Write(Data | BackLight_State);
  I2C_Master_Stop();
}
 
void LCD_Write_4Bit(unsigned char Nibble)
{
  // Get The RS Value To LSB OF Data
  Nibble |= RS;
  IO_Expander_Write(Nibble | 0x04);
  IO_Expander_Write(Nibble & 0xFB);
  __delay_us(50);
}
 
void LCD_Cmd(unsigned char Cmd)
{
  RS = 0; // Command Register Select
  LCD_Write_4Bit(Cmd & 0xF0);
  LCD_Write_4Bit((Cmd << 4) & 0xF0);
}
 
void LCD_Write_Char(char Data)
{
  RS = 1; // Data Register Select
  LCD_Write_4Bit(Data & 0xF0);
  LCD_Write_4Bit((Data << 4) & 0xF0);
}
 
void LCD_Write_String(char* Str)
{
  for(int i=0; Str[i]!='\0'; i++)
    LCD_Write_Char(Str[i]);
}
 
void LCD_Set_Cursor(unsigned char ROW, unsigned char COL)
{
  switch(ROW)
  {
    case 1:
      LCD_Cmd(0x80 + COL-1);
      break;
    case 2:
      LCD_Cmd(0xC0 + COL-1);
      break;
    case 3:
      LCD_Cmd(0x94 + COL-1);
      break;
    case 4:
      LCD_Cmd(0xD4 + COL-1);       
  }
}
 
void Backlight()
{
  BackLight_State = LCD_BACKLIGHT;
  IO_Expander_Write(0);
}
 
void noBacklight()
{
  BackLight_State = LCD_NOBACKLIGHT;
  IO_Expander_Write(0);
}
 
void LCD_SL()
{
  LCD_Cmd(0x18);
  __delay_us(40);
}
 
void LCD_SR()
{
  LCD_Cmd(0x1C);
  __delay_us(40);
}
 
void LCD_Clear()
{
  LCD_Cmd(0x01);
  __delay_us(40);
}

void LCD_Write_CharXY(char byte, unsigned char x, unsigned char y)
{
     LCD_Set_Cursor(x, y);
     LCD_Write_Char(byte);
}


void LCD_Write_StringXY(char* arr, unsigned char x, unsigned char y)
{
    LCD_Set_Cursor(x, y);
    LCD_Write_String(arr);
}


