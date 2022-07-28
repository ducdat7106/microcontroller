/*
 * File:   main_triac.c
 * Author: NGUYEN DUC DAT
 *
 * Created on 4 January, 2022, 3:28 AM
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000

#include <xc.h>
#include"adc.h"

#define triac_gate PORTDbits.RD7
#define tris_triac_gate TRISDbits.TRISD7

int ZC = 0; //zero-crossing
int alpha;

void delay_us(unsigned int value);


void ExtInt()// external interrupt ISR
{
    //OPTION_REG = 0b00000000;  // Enables PULL UPs -> no need res external
    INTE=1;
    GIE=1;
}

void __interrupt() ISR()
{
    if(INTE&&INTF)
    {
        INTF=0;// clear the interrupt flag after done with it
        ZC=1;
    }
}


void main(void) 
{
    ADC_Init();
    
    tris_triac_gate = 0;//as output
    
    ExtInt();
    
    /*
        The frequency of my AC source is 50Hz which means the period is 20ms, 
     so the half wave period is 10 ms = 10000 us.
    */
    while(1)
    {
        alpha = ( 1023 - ADC_Read(0) ) * 10;
        
        if (alpha > 9500)
            alpha = 9500;
        else if (alpha < 200)
            alpha = 0;
        
        while(ZC == 0) ;    // wait for zero crossing event
        
         // send firing pulse after alpha
        triac_gate=1;
        delay_us(alpha);
        triac_gate=0;
        __delay_us(200);

        ZC = 0;
    }
    
    return;
}

void delay_us(unsigned int value)
{
    /*
    F = 20 MHz --> T = 0.2us
    --> 1 us = T*5
    */
    value *= 5;
    while( value--);
       
}
// End of code

