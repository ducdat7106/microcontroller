/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 22 November, 2021, 8:10 AM
 */

#include <xc.h>
#include"config.h"

#define _XTAL_FREQ 16000000

#define led1 PORTDbits.RD0
#define led2 PORTDbits.RD1
#define led3 PORTDbits.RD2
#define led4 PORTDbits.RD3
#define tris_led1 TRISDbits.TRISD0
#define tris_led2 TRISDbits.TRISD1
#define tris_led3 TRISDbits.TRISD2
#define tris_led4 TRISDbits.TRISD3

void changePortB()
{
    RBIE=1;
    GIE=1;
}

void __interrupt() ISR()
{
    if(RBIE&&RBIF)
    {
        if(RB4==1)
            led1=~led1;
        if(RB5==1)
            led2=~led2;
        if(RB6==1)
            led3=~led3;
        if(RB7==1)
            led4=~led4;
        RBIF=0;//cho xuong cuoi moi chay duoc
    }
}

void main(void) 
{
    ADCON1=0x07;
    
    tris_led1=0;
    tris_led2=0;
    tris_led3=0;
    tris_led4=0;
    
    led1=led2=led3=led4=0;
    
    changePortB();
    
    while(1)
    {
        led4=0;
        __delay_ms(1000);
        led4=1;
        __delay_ms(1000);
    }
    
    return;
}
