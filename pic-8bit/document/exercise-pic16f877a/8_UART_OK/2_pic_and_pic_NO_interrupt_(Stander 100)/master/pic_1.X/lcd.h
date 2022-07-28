/* 
 * File:   lcd.h
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 7:08 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

//***********************************************************************
#include<xc.h>
    
#define LCD_EN_Delay 500

#define LCD_DATA_PORT_D TRISD	//Data Bus Direction_ huong bus du lieu

#define LCD_RS_D TRISD2

#define LCD_EN_D TRISD3
    
#define RS RD2 // LCD register select line
#define EN RD3 //LCD enable
//#define RW PORTDbits.RD5 // LCD read/write line //noi dat tren mach phan cung

#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
//==========================================
/* 16x2 LCD Specification */
#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTwo 0xc0
#define BlankSpace ' '

//-----[ Prototypes For All Functions ]-----

void LCD_Init();
void LCD_Clear();

void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);

void LCD_Set_Cursor(unsigned char, unsigned char);
void LCD_Write_Char(unsigned char);
void LCD_Write_String(char*);
void LCD_Write_Number(unsigned int number);


void LCD_Shift_Right();
void LCD_Shift_Left();
//------------------------------------------


// Command set for Hitachi 44780U LCD display controller
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_CURSOR_BACK 0x10
#define LCD_CURSOR_FWD 0x14
#define LCD_PAN_LEFT 0x18
#define LCD_PAN_RIGHT 0x1C
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_BLINK 0x0F
#define LCD_CURSOR_LINE2 0xC0

// display controller setup commands from page 46 of Hitachi datasheet
#define FUNCTION_SET 0x28 // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE 0x06 // increment mode
#define DISPLAY_SETUP 0x0C // display on, cursor off, blink offd




//****************************************************************************
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

