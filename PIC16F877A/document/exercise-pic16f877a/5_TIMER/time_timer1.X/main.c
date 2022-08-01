/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 24 November, 2021, 11:11 AM
 */


#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void time1()
{
    TMR1 = 15535;
    T1CONbits.T1CKPS1 = //1:4
    T1CONbits.T1CKPS0 = 0;
    
    T1CONbits.TMR1CS = 0;
    
    T1CONbits.T1SYNC = 1;
    T1CONbits.TMR1ON = 1;
    
    TMR1IE=1;
    PEIE=1;
    GIE=1;
}
//10ms ngat 1 lan
void __interrupt() timer1()
{
    if(TMR1IE && TMR1IF)
    {
        TMR1=15535;
        RC0 =~RC0;//toggle the LED
        TMR1IF=0;
    }
}

void main(void) 
{
    ADCON1=0x06;
    TRISCbits.TRISC0 = 0;
    RC0=0;
    time1();
    while(1)
    {
        
    }
    return;
}
