/*
 * File:   main_ds18b20.c
 * Author: Nguyen Duc Dat
 *
 * Created on 25 December, 2021, 8:29 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//#define _XTAL_FREQ 8000000

#include <xc.h>
#include"ds18b20.h"
#include"i2c_lcd.h"
#include"i2c_master.h"

uint16_t raw_temp;
char     temp[] = "000.0000 C";

void main(void) 
{
    CMCON |=7;
    ADCON1 = 0x06;
    
    __delay_ms(1000);   // wait 1 second
 
    LCD_Init(100000);        // initialize LCD module
    LCD_Set_Cursor(1,3);    // move cursor to column 3, row 1
    LCD_Write_String("Temperature:");

    temp[8] = 223;   // put degree symbol ( ° )

    while(1)
    {
        
      if(ds18b20_read(&raw_temp))
      {
        if(raw_temp & 0x8000)  // if the temperature is negative
        {
          temp[0] = '-';             // put minus sign (-)
          raw_temp = (~raw_temp) + 1;  // change temperature value to positive form
        }

        else
        {
          if((raw_temp >> 4) >= 100)  // if the temperature >= 100 °C
            temp[0] = '1';            // put 1 of hundreds
          else                        // otherwise
            temp[0] = ' ';            // put space ' '
        }

        // put the first two digits ( for tens and ones)
        temp[1] = ( (raw_temp >> 4) / 10 ) % 10 + '0';  // put tens digit
        temp[2] =   (raw_temp >> 4)        % 10 + '0';  // put ones digit

        // put the 4 fraction digits (digits after the point)
        // why 625?  because we're working with 12-bit resolution (default resolution)
        temp[4] = ( (raw_temp & 0x0F) * 625) / 1000 + '0';          // put thousands digit
        temp[5] = (((raw_temp & 0x0F) * 625) / 100 ) % 10 + '0';    // put hundreds digit
        temp[6] = (((raw_temp & 0x0F) * 625) / 10 )  % 10 + '0';    // put tens digit
        temp[7] = ( (raw_temp & 0x0F) * 625) % 10 + '0';            // put ones digit

        LCD_Set_Cursor(2,4);     // move cursor to column 4 row 2
        LCD_Write_String(temp);    // print temp
      }

      else
      {
        LCD_Set_Cursor(2, 4);          // move cursor to column 4 row 2
        LCD_Write_String("  Error!  ");
      }

      __delay_ms(1000);   // wait 1 second
         
    }
}
