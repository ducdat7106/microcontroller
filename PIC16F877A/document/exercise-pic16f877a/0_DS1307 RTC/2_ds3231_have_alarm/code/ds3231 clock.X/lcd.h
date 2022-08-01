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

#include<xc.h>
    
    
#define LCD_FIRST_ROW          0x80 //Move cursor to the 1st row
#define LCD_SECOND_ROW         0xC0 //Move cursor to the 2nd row
#define LCD_THIRD_ROW          0x94 //Move cursor to the 3rd row
#define LCD_FOURTH_ROW         0xD4 //Move cursor to the 4th row

#define LCD_TURN_OFF           0x08 //Turn Lcd display off
#define LCD_TURN_ON            0x0C //Turn Lcd display on
#define LCD_UNDERLINE_ON       0x0E //Underline cursor on
#define LCD_CURSOR_OFF         0x0C //Turn off cursor
#define LCD_BLINK_CURSOR_ON    0x0F //Blink cursor on
#define LCD_SHIFT_LEFT         0x18 //Shift display left without changing display data RAM
#define LCD_SHIFT_RIGHT        0x1C //Shift display right without changing display data RAM
#define LCD_MOVE_CURSOR_LEFT   0x10 //Move cursor left without changing display data RAM
#define LCD_MOVE_CURSOR_RIGHT  0x14 //Move cursor right without changing display data RAM
#define LCD_CLEAR              0x01 //Clear display
#define LCD_RETURN_HOME        0x02 //Return cursor to home position, returns a shifted display to its original position. Display data RAM is unaffected
#define LCD_ENTRY_MODE_SET     0x04



#ifndef LCD_TYPE
   #define LCD_TYPE 2           // 0=5x7, 1=5x10, 2=2 lines
#endif


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
void LCD_SL();
void LCD_SR();
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_Set_Cursor(unsigned char, unsigned char);
void LCD_Write_Char(char);
void LCD_Write_String(char*);
void LCD_Write_Number(unsigned int number);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

