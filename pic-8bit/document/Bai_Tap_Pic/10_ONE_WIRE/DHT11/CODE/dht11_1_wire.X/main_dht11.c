/*
 * File:   main_dht11.c
 * Author: NGUYEN DUC DAT
 *
 * Created on 4 January, 2022, 5:12 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 8000000

// DHT11 sensor connection (here data pin is connected to RB0)
#define DHT11_PIN      RB0
#define DHT11_PIN_DIR  TRISB0

#include <xc.h>
#include"lcd.h"
#include"dht11.h"

// variables declaration
char Temperature[] = "Temp = 00.0 C  ";
char Humidity[]    = "RH   = 00.0 %  ";

unsigned char T_Byte1, T_Byte2, RH_Byte1, RH_Byte2, CheckSum ;



void system_init();


void main(void) {
    
    system_init();
    
    while(1)
    {
        Start_Signal();     // send start signal to the sensor
        if(Check_Response())    // check if there is a response from sensor (If OK start reading humidity and temperature data)
        {
            // read (and save) data from the DHT11 sensor and check time out errors
            if(Read_Data(&RH_Byte1) || Read_Data(&RH_Byte2) || Read_Data(&T_Byte1) || Read_Data(&T_Byte2) || Read_Data(&CheckSum))
            {
                LCD_Clear();       // clear LCD
                LCD_Set_Cursor(2, 5);           // go to column 5, row 2
                LCD_Write_String("Time out!");   // display "Time out!"
            }

            else         // if there is no time out error
            {
              if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF))
              {                                       // if there is no checksum error
                  Temperature[7]  = T_Byte1 / 10  + '0';
                  Temperature[8]  = T_Byte1 % 10  + '0';
                  Temperature[10] = T_Byte2 / 10  + '0';
                  Humidity[7]     = RH_Byte1 / 10 + '0';
                  Humidity[8]     = RH_Byte1 % 10 + '0';
                  Humidity[10]    = RH_Byte2 / 10 + '0';
                  Temperature[11] = 223;    // put degree symbol (°)
                  LCD_Set_Cursor(1, 1);           // go to column 1, row 1
                  LCD_Write_String(Temperature);
                  LCD_Set_Cursor(2, 1);           // go to column 1, row 2
                  LCD_Write_String(Humidity);
              }

              // if there is a checksum error
              else
              {
                  LCD_Clear();       // clear LCD
                  LCD_Set_Cursor(1, 1);           // go to column 1, row 1
                  LCD_Write_String("Checksum Error!");
              }

            }
        }
        // if there is a response (from the sensor) problem
        else
        {
            LCD_Clear();      // clear LCD
            LCD_Set_Cursor(1, 3);           // go to column 3, row 1
            LCD_Write_String("No response");
            LCD_Set_Cursor(2, 1);           // go to column 1, row 2
            LCD_Write_String("from the sensor");
        }
 
    TMR1ON = 0;        // disable Timer1 module
    __delay_ms(1000);  // wait 1 second
 
    }
    return;
}

/*
 used Timer1 module to measure signal widths (logic 1 and logic 0 widths),
it is configured to increment every 1 us.
*/
void system_init()
{
    ADCON1 =0x06;
    
    T1CON  = 0x10;        // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
    TMR1H  = 0;           // reset Timer1
    TMR1L  = 0;
    
    LCD_Init();
    
    
}

// End of code.