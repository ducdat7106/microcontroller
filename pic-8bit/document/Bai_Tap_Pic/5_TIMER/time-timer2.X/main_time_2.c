/*
 * File:   main_time_2.c
 * Author: Dat Nguyen
 *
 * Created on 26 November, 2021, 10:43 PM
 */


#include <xc.h>

#define _XTAL_FREQ 16000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void timer2()
{
    TOUTPS3=0;//1:1
    TOUTPS2=0;
    TOUTPS1=0;
    TOUTPS0=0;
    
    TMR2ON=1;
    
    T2CKPS1=1;//1:16
    //T2CKPS0=X;
    
    PR2=124;
    
    TMR2IE=1;
    TMR2IF=0;
    
    PEIE=1;
    GIE=1;
}

void __interrupt() time2()
{
    if(TMR2IE && TMR2IF)
    {
        RD4=~RD4;
        PR2=124;
        TMR2IF=0;
    }
}
void main(void) 
{
    ADCON1=0x06;
    
    TRISD4=0;
    RD4=0;
    
    timer2();
    while(1)
    {
        
    }
    return;
}
