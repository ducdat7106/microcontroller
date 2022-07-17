#include"lcd.h"


/*
 Sending Data To The LCD
 */
void LCD_DATA(unsigned char Data)
{
  if(Data & 1)
    D4 = 1;
  else
    D4 = 0;
  if(Data & 2)
    D5 = 1;
  else
    D5 = 0;
  if(Data & 4)
    D6 = 1;
  else
    D6 = 0;
  if(Data & 8)
    D7 = 1;
  else
    D7 = 0;
}

/*
   Sending Commands To The LCD
 */
void LCD_CMD(unsigned char CMD)
{
  // Select Command Register
  RS = 0;
  // Move The Command Data To LCD
  LCD_DATA(CMD);
  // Send The EN Clock Signal
  EN = 1;
  
  if(CMD<=0x02)
  {
      __delay_ms(2);
  }else{
      __delay_us(50);
  }
  __delay_us(LCD_EN_Delay);
  EN = 0;
}


/*
 Initializing The LCD Module
*/
void LCD_Init()
{
  // IO Pin Configurations
  LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;
  LCD_EN_D = 0;
  // The Init. Procedure As Described In The Datasheet
  LCD_DATA(0x00);
  __delay_ms(30);
  __delay_us(LCD_EN_Delay);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_us(150);
  LCD_CMD(0x03);
  LCD_CMD(0x02);
  LCD_CMD(0x02);
  LCD_CMD(0x08);//Display off
  LCD_CMD(0x00);
  LCD_CMD(0x0C);//Display on, cursor off
  LCD_CMD(0x00);
  LCD_CMD(0x06);//Cursor increment to the right, no shift
}
/*
  Writing A Character To The LCD
 */
void LCD_Write_Char(char Data)
{
  char Low4,High4;
  Low4 = Data & 0x0F;
  High4 = Data & 0xF0;
  RS = 1;
  LCD_DATA(High4>>4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
  LCD_DATA(Low4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
}

/*
 Writing Text To The LCD
 */
void LCD_Write_String(char *str)
{
  int i;
  for(i=0;str[i]!='\0';i++)
    LCD_Write_Char(str[i]);
}

/*
 LCD Clear
 */
void LCD_Clear()
{
    LCD_CMD(0);
    LCD_CMD(1);
    __delay_ms(2);
}

/*
 Set LCD Cursor Position
 
 0x80 + add

 r -> row number, c -> column number.

  And the cursor position offset is calculated from the base 0x80
 */
void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
  else if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
}

/*
 *Shift Entire Display Left
 * 
 * shift entier display left        0x18
 */
void LCD_SL()
{
  LCD_CMD(0x01);
  LCD_CMD(0x08);
}

/*
 Shift Entire Display Right 
 
 shift entire display right     0x1C 
 */
void LCD_SR()
{
  LCD_CMD(0x01);
  LCD_CMD(0x0C);
}

void LCD_Write_Number(long number)
{
    unsigned int num[10];
    char c;
    //int p=0;
    int length=-1;
    
    if(number == 0)
    {
        c = (char)(number + '0');
        LCD_Write_Char(c);
    }
    else if(number != 0)
    {
        while(number>0)
        {
            length++;
            num[length]=number%10;
            number = number/10;
        }
    

        for(int p=length; p>=0; p--)
        {
            c = (char)(num[p] + '0');
            LCD_Write_Char(c);
        }
    }
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

void LCD_Write_NumberXY(long number, unsigned char x, unsigned char y)
{
    LCD_Set_Cursor(x, y);
    LCD_Write_Number(number);
}