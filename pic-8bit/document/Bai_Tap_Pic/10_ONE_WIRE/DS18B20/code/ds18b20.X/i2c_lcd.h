/* 
 * File:   i2c_lcd.h
 * Author: Nguyen Duc Dat
 *
 * Created on 5 December, 2021, 10:49 PM
 */

#ifndef I2C_LCD_H
#define	I2C_LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
 
#include <xc.h>
#include"i2c_master.h"
 
//#define _XTAL_FREQ            16000000
//#define I2C_BaudRate          100000

#define SCL_D                 TRISC3
#define SDA_D                 TRISC4
 
#define LCD_BACKLIGHT         0x08
#define LCD_NOBACKLIGHT       0x00
#define LCD_FIRST_ROW         0x80
#define LCD_SECOND_ROW        0xC0
#define LCD_THIRD_ROW         0x94
#define LCD_FOURTH_ROW        0xD4
#define LCD_CLEAR             0x01
#define LCD_RETURN_HOME       0x02
#define LCD_ENTRY_MODE_SET    0x04
#define LCD_CURSOR_OFF        0x0C
#define LCD_UNDERLINE_ON      0x0E
#define LCD_BLINK_CURSOR_ON   0x0F
#define LCD_MOVE_CURSOR_LEFT  0x10
#define LCD_MOVE_CURSOR_RIGHT 0x14
#define LCD_TURN_ON           0x0C
#define LCD_TURN_OFF          0x08
#define LCD_SHIFT_LEFT        0x18
#define LCD_SHIFT_RIGHT       0x1E
#define LCD_TYPE              2 // 0 -> 5x7 | 1 -> 5x10 | 2 -> 2 lines

    
#define I2C_address  0x4E

//---[ LCD Routines ]---

//Initialize I2C Master with 100KHz clock --> OK
void LCD_Init(const unsigned long I2C_BaudRate);
void LCD_Set_Cursor(unsigned char ROW, unsigned char COL);
void LCD_Clear();
void LCD_Write_Char(char);
void LCD_Write_String(char*);

void Backlight();
void noBacklight();
void LCD_SR();
void LCD_SL();


void IO_Expander_Write(unsigned char Data);
void LCD_Write_4Bit(unsigned char Nibble);
void LCD_CMD(unsigned char CMD);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_LCD_H */

