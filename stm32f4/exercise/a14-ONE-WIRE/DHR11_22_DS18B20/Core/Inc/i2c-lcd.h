/** 
Edit by modify: Ngoc Hang 
**/

#include "stm32f4xx_hal.h"

void LCD_Init (void);   // initialize lcd

void LCD_Send_Cmd (char cmd);  // send command to the lcd

void LCD_Write_Char (char data);  // send data to the lcd

void LCD_Write_String (char *str);  // send string to the lcd

void LCD_Clear (void);	//clear display lcd

void LCD_Set_Cursor (int row, int col); //set proper location on screen
