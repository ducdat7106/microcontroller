/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 7:08 AM
 */

#include <xc.h>
#include "lcd.h"

void main(void) 
{
    ADCON1 = 0x06;
    
    LCD_Init();
    LCD_Clear();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("DUC DAT");
    LCD_Set_Cursor(2,1);
    LCD_Write_Number(300720001);
    __delay_ms(2000);
    
    while(1)
    {
        for(int i=0; i<4; i++)
        {
          __delay_ms(300);
          LCD_SR();
        }
        for(int i=0; i<4; i++)
        {
          __delay_ms(300);
          LCD_SL();
        }
    }
    return;
}