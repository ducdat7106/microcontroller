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
    
    
#define LCD_FIRST_ROW          0x80
#define LCD_SECOND_ROW         0xC0
#define LCD_THIRD_ROW          0x94
#define LCD_FOURTH_ROW         0xD4

#define LCD_TURN_OFF           0x08
#define LCD_UNDERLINE_ON       0x0E
#define LCD_CURSOR_OFF         0x0C // Lcd_Cmd(_LCD_CURSOR_OFF); // cursor off
#define LCD_BLINK_CURSOR_ON    0x0F
#define LCD_SHIFT_LEFT         0x18
#define LCD_SHIFT_RIGHT        0x1C
#define LCD_MOVE_CURSOR_LEFT   0x10
#define LCD_MOVE_CURSOR_RIGHT  0x14
#define LCD_CLEAR              0x01//Lcd_Cmd(_LCD_CLEAR);      // clear LCD
#define LCD_RETURN_HOME        0x02
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

