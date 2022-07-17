#include"lcd.h"

/*
0x28 is used for 4-bit data initialization.
0x0C for making LCD display on and cursor off.
0X01 for clearing the display of the LCD.
0x06 for increment cursor (shift cursor to right)
0x80 // move the Cursor to First line First Position
*/
void LCD_Init()
{
  // IO Pin Configurations
  LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;
  LCD_EN_D = 0;
  
  // The Init. Procedure As Described In The Datasheet
  LCD_Set_Bit(0x00);
  __delay_us(LCD_EN_Delay);  
  __delay_ms(30);
  
  LCD_Cmd(0x03);
  __delay_ms(5);
  LCD_Cmd(0x03);
  __delay_ms(5);
  LCD_Cmd(0x03);
  __delay_ms(5);
  
  LCD_Cmd(0x02);//02H is used for Return home -> Clears the RAM and initializes the LCD
  LCD_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  LCD_Cmd(0x08);//Select Row 1
  LCD_Cmd(0x00); //Clear Row 1 Display
  LCD_Cmd(0x0C);//Select Row 2
  LCD_Cmd(0x00);//Clear Row 2 Display
  LCD_Cmd(0x06);
}

void LCD_Clear()
{
  LCD_Cmd(0);//Clear the LCD
  LCD_Cmd(1);//Move the curser to first position
}

void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;//Lower 8-bits
    Low4 = Temp & 0x0F;//Upper 8-bits
    LCD_Cmd(High4);//Set Row
    LCD_Cmd(Low4);//Set Column
  }
  else if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;//Lower 8-bits
    Low4 = Temp & 0x0F;//Upper 8-bits
    LCD_Cmd(High4);//Set Row
    LCD_Cmd(Low4);//Set Column
  }
}

void LCD_Write_Char(char Data)//Send 8-bits through 4-bit mode
{
  char Low4,High4;// char Lower_Nibble,Upper_Nibble
  Low4 = Data & 0x0F;
  High4 = Data & 0xF0;
  RS = 1;
  LCD_Set_Bit(High4>>4);//Send upper half by shifting by 4
  EN = 1;
  __delay_us(LCD_EN_Delay);//  for(int i=2130483; i<=0; i--)  NOP(); 
  EN = 0;
  __delay_us(LCD_EN_Delay);
  LCD_Set_Bit(Low4);//Send Lower half
  EN = 1;
  __delay_us(LCD_EN_Delay);//  for(int i=2130483; i<=0; i--)  NOP(); 
  EN = 0;
  __delay_us(LCD_EN_Delay);
}

void LCD_Write_String(char *str)
{
  int i;
  for(i=0; str[i]!='\0'; i++)
    LCD_Write_Char(str[i]);//Split the string using pointers and call the Char function 
}

void LCD_SL()//left shift 
{
  LCD_Cmd(0x01);
  LCD_Cmd(0x08);
}

void LCD_SR()//right shift 
{
  LCD_Cmd(0x01);
  LCD_Cmd(0x0C);
}

void LCD_Write_Number(unsigned int number)
{
    unsigned int num[10];
    char c;
    int p=0;
    int k=0;
    
    if(number == 0)
    {
        c = (char)(number + '0');
        LCD_Write_Char(c);
    }
    else if(number != 0)
    {
        while(number>0)
        {
        num[k]=number%10;
        number = number/10;
        k++;
        }
    
        k--;
        for(p=k; p>=0; p--)
        {
            c = (char)(num[p] + '0');
            LCD_Write_Char(c);
        }
    }
}

//Based on the Hex value Set the Bits of the Data Lines
void LCD_Set_Bit(unsigned char Data_Bit)
{
  if(Data_Bit & 1)
    D4 = 1;
  else
    D4 = 0;
    
  if(Data_Bit & 2)
    D5 = 1;
  else
    D5 = 0;
    
  if(Data_Bit & 4)
    D6 = 1;
  else
    D6 = 0;
    
  if(Data_Bit & 8)
    D7 = 1;
  else
    D7 = 0;
}

void LCD_Cmd(char Cmd)//Command
{
  RS = 0;// Select Command Register
  LCD_Set_Bit(Cmd);// Move The Command Data To LCD   // or // Send The EN Clock Signal  or //Incoming Hex value
  EN = 1;  // Send The EN Clock Signal
  __delay_ms(4);
  EN = 0;
}
