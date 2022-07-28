/*
 * File:   main_WDT.c
 * Author: Dat Nguyen
 *
 * Created on 30 November, 2021, 4:58 AM
 */


#include <xc.h>

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//#define _XTAL_FREQ  internal chip = 31,25Khz  
/*
// watchdog overflow time calculation
// according to device datasheet
// at no prescalar (1:1), the overflow
// time is following.
// min typ max
// 7 18 33 (ms)
// WDT Overflow = Tcons * prescalar
// = 18(ms) * 128
// = 2.304 sec
*/

void WDT_Init()
{
    T0CS = 0; //using the internal clock
    T0SE = 0; //LOW to HIGH transmit
    
    PS0 = 0; //?????
    PS1 = 1; // prescalar 128 -->1024ms ~~1s
    PS2 = 1; //?????
    PSA = 1; // Prescaler is assigned to the WDT
}

void main(void) 
{
    unsigned int i=0;
    ADCON1=0x07;
    TRISC=0x00;
    PORTC=1;
    //__delay_ms(500);
    WDT_Init();
    while(1)
    {
        
         
        PORTC=1;
        /*
        for(i=0;i<100; i++);
        //SLEEP();// awake when WDT overflow approx. 2.3 Sec
        PORTC=1;
        for(i=0;i<100; i++);
        //SLEEP();// awake when WDT overflow approx. 2.3 Sec       
        CLRWDT(); // clear WDT
             */
    }
    return;
}
