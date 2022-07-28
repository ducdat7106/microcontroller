/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 24 November, 2021, 8:33 AM
 */
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
/*
    Delay Calculations for 1ms @20Mhz with Prescalar as 32:
    RegValue = 256-(Delay * Fosc)/(Prescalar*4))
    = 256-((1ms * 20Mhz)/(32*4)) = 256-156=100
 
 */
void timer0()
{
    PS2=1; PS1=0; PS0=0;//1 : 32
    
    PSA=0;
    T0SE=0;
    T0CS=0;
    
    GIE=1; //Enable Global Interrupt
    
    TMR0=100;       // Load the time value for 1ms delay
    
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
}

void __interrupt() time()
{
    if(TMR0IE&&TMR0IF)
    {
        RD0=~RD0;
        TMR0 = 101; /*Load the timer Value, (Note: Timer value is 101 instaed of 100 as the
                    TImer0 needs two instruction Cycles to start incrementing TMR0) */
        
        TMR0IF=0; // Clear timer interrupt flag
    }
}

void main(void) 
{
    ADCON1=0x06;
    TRISD0=0x00;
    
    timer0();
    
    while(1)
    {
        
    }
    return;
}
