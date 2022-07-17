/*
 * File:   main.c
 * Author: Nguyen Duc Dat
 *
 * Created on 3 December, 2021, 10:02 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 4000000

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

unsigned const font[] = {
65, 127, 127,  65,  64,  96, 112,   0, //'L'
124, 126,  19,  19, 126, 124,   0,   0, //'A'
127, 127,  14,  28,  14, 127, 127,   0, //'M'
0,   0,   0,   0,   0,   0,   0,   0, //' '
34,  99,  73,  73, 127,  54,   0,   0, //'3'
0,   0,   0,   0,   0,   0,   0,   0, //' '
127, 127,   6,  12,  24, 127, 127,   0, //'N'
28,  62,  99,  65,  81, 115, 114,   0, //'G'
28,  62,  99,  65,  99,  62,  28,   0, //'O'
127, 127,   6,  12,  24, 127, 127,   0, //'N'
0,   0,   0,   0,   0,   0,   0,   0, //' '
0,   0,   0,   0,   0,   0,   0,   0, //' '
};


void main() 
{
unsigned scroll, refresh, col;
TRISB = 0x00;  
TRISC = 0x00;  
PORTB = 0x00;  
PORTC = 0x00;  
   while(1)
   {
    for(scroll=0;scroll<96;scroll++)
    { //font. 12 x 8[8x8 matrix] = 104.
     for(refresh=0;refresh<20;refresh++)
     {  
      PORTCbits.RC0 = 1; PORTCbits.RC0 = 0; PORTCbits.RC1 = 1; PORTCbits.RC3 = 1; PORTCbits.RC3 = 0; 
      for(col=0;col<16;col++) // 16 hang va cot
      { 
      PORTB =~ font[col + scroll];
      __delay_us(300);  
      PORTCbits.RC0 = 1; PORTCbits.RC0 = 0; PORTCbits.RC1 = 0; PORTCbits.RC3 = 1; PORTCbits.RC3 = 0;
      }
     }
    }
   }
}