
#include <stdio.h>

//#include "stm32f1xx_hal.h"
#include "stm32f4xx_hal.h"

//no using -->command
#define LCD16 16
//#define LCD20 20


extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup



void LCD_Init (void);   // initialize lcd

void LCD_Send_Cmd (char cmd);  // send command to the lcd

void LCD_Write_Char (char data);  // send data to the lcd

void LCD_Write_String (char *str);  // send string to the lcd

void LCD_Clear (void);	//clear display lcd

void LCD_Set_Cursor (int row, int col); //set proper location on screen
