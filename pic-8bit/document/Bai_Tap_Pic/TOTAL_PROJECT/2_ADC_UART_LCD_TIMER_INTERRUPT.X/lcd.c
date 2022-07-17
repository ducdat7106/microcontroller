#include"lcd.h"

//-----[ Alphanumeric LCD 16x2 Routines ]-----


/*
	write data
*/
void LCD_DATA(unsigned char Data) //Based on the Hex value Set the Bits of the Data Lines
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
	write command
*/
void LCD_CMD(unsigned char CMD)
{
  // Select Command Register
  RS = 0;
  
  // Move The Command Data To LCD
  LCD_DATA(CMD);//Incoming Hex value
  
  // Send The EN Clock Signal
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
}

/*
	clear screen
*/
void LCD_Clear()
{
  LCD_CMD(0); //Clear the LCD
  LCD_CMD(1);//Move the curser to first position
}

/*
	goto row, column (1 or 2)
*/
void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;//Lower 8-bits
    Low4 = Temp & 0x0F;//Upper 8-bits
    LCD_CMD(High4);//Set Row
    LCD_CMD(Low4);//Set Column
  }
  if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
}


/*
	initialization 
*/
void LCD_Init()
{
  // IO Pin Configurations
  LCD_DATA_PORT_D = 0x00;// clear latches before enabling TRIS bits
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
  
  LCD_CMD(0x02);//02H is used for Return home -> Clears the RAM and initializes the LCD
  LCD_CMD(0x02);//02H is used for Return home -> Clears the RAM and initializes the LCD
  LCD_CMD(0x08);//Select Row 1
  LCD_CMD(0x00);//Clear Row 1 Display
  LCD_CMD(0x0C);//Select Row 2
  LCD_CMD(0x00);//Clear Row 2 Display
  LCD_CMD(0x06);
}

void LCD_Write_Char(char Data)
{
  char Low4,High4;
  Low4 = Data & 0x0F;
  High4 = Data & 0xF0;
  RS = 1;
  LCD_DATA(High4>>4); //Send upper half by shifting by 4
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
  LCD_DATA(Low4);//Send Lower half
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
}


void LCD_Write_String(char *str)
{
  int i;
  for(i=0;str[i]!='\0';i++)
    LCD_Write_Char(str[i]);  //Split the string using pointers and call the Char function 
}

void LCD_Shift_Right()
{
	LCD_CMD(0x01);
	LCD_CMD(0x0C);
}

void LCD_Shift_Left()
{
	LCD_CMD(0x01);
	LCD_CMD(0x08);
}

