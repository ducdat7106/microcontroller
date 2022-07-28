#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
   
//LCD Commands
/*
  Hex Code	Command to LCD Instruction Register
		0F	LCD ON, cursor ON
		01	Clear display screen
		02	Return home
		04	Decrement cursor (shift cursor to left)
		06	Increment cursor (shift cursor to right)
		05	Shift display right
		07	Shift display left
		0E	Display ON, cursor blinking
		80	Force cursor to beginning of first line
		C0	Force cursor to beginning of second line
		38	2 lines and 5×7 matrix
		83	Cursor line 1 position 3
		3C	Activate second line
		08	Display OFF, cursor OFF
		C1	Jump to second line, position 1
		OC	Display ON, cursor OFF
		C1	Jump to second line, position 1
		C2	Jump to second line, position 2 
*/   
    
#define LCD_EN_Delay 500
    
#define LCD_DATA_PORT_D TRISD	//Data Bus Direction_ huong bus du lieu
#define LCD_RS_D TRISD2
#define LCD_EN_D TRISD3
    
#define RS RD2 //LCD register select line
#define EN RD3 //LCD enable
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
    
void LCD_Init();
void LCD_Clear();
void LCD_Set_Cursor(unsigned char, unsigned char);
void LCD_Write_Char(char);
void LCD_Write_String(char*);
void LCD_Write_Number(unsigned int number);


void LCD_SL();
void LCD_SR();
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

