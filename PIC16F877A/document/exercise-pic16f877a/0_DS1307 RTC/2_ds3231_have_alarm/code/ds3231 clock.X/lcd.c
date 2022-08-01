#include"lcd.h"


void LCD_DATA(unsigned char Data)
{
	/*
	  Sending Data To The LCD
	*/
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


void LCD_CMD(unsigned char CMD)
{
  /*
  Sending Commands To The LCD
  */
  RS = 0;	// Select Command Register
  LCD_DATA(CMD);	// Move The Command Data To LCD
  EN = 1;	// Send The EN Clock Signal
  __delay_us(LCD_EN_Delay);
  EN = 0;
}


void LCD_Clear()
{
	/*
	LCD Clear
	*/
  LCD_CMD(0);
  LCD_CMD(1);//0x01
}
void LCD_Set_Cursor(unsigned char row, unsigned char column)
{
	/*
		Set LCD Cursor Position
		row = 1,2
		column = 1,2,3,...,16
	*/
  unsigned char Temp,Low4,High4;
  
  if(row == 1)
  {
    Temp = 0x80 + column - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
  else if(row == 2)
  {
    Temp = 0xC0 + column - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
  else if(row == 3)
  {
  	Temp = 0x94 + column - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
  else if(row == 4)
  {
  	Temp = 0xD4 + column - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
}
void LCD_Init()
{
	/*
	Initializing The LCD Module
	*/
	
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
  LCD_CMD(0x08);
  LCD_CMD(0x00);
  LCD_CMD(0x0C);
  LCD_CMD(0x00);
  LCD_CMD(0x06);
}

void LCD_Write_Char(char Data)
{
	
	/*
	Writing A Character To The LCD
	*/
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

void LCD_Write_String(char *str)
{
  unsigned int i;
  for(i=0;str[i]!='\0';i++)
    LCD_Write_Char(str[i]);
}

void LCD_SL()
{
  LCD_CMD(0x01);
  LCD_CMD(0x08);
}

void LCD_SR()
{
  LCD_CMD(0x01);
  LCD_CMD(0x0C);
}

void LCD_Write_Number(unsigned int number)
{
    int num[10];
    unsigned char c;
    int p;
    unsigned  int k=0;
    
    if(number == 0)
    {
    	c = 0 + '0';
    	LCD_Write_Char(c);
	}
	else if(number>0)
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
	        c=num[p] + '0';
	        LCD_Write_Char(c);
	    }
	}
    
    return;
}
