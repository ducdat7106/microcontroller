#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
    
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

