/* 
 * File:   lcd.h
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 8:09 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

void Lcd_SetBit(char data_bit);
void Lcd_Cmd(char a);
void Lcd_Clear();
void Lcd_Set_Cursor(char a, char b);
void Lcd_Start();
void Lcd_Print_Char(char data);
void Lcd_Print_String(char *a);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

