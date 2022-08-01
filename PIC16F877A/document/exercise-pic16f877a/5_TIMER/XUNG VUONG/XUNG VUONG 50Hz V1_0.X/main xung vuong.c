/*
 * File:   main.c
 * Author: Nguyen Duc Dat
 *
 * Created on 15 December, 2021, 2:57 AM
 */

#pragma config FOSC = XT        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include<stdint.h>

#define _XTAL_FREQ 8000000

#define LED PORTDbits.RD0
#define TRIS_LED TRISDbits.TRISD0

#define LED_1 PORTDbits.RD1
#define TRIS_LED_1 TRISDbits.TRISD1

#define LED2 PORTDbits.RD2
#define TRIS_LED2 TRISDbits.TRISD2

volatile int value_10 = 0;//bien thay doi ko bao trc
volatile int value_5 = 0;
volatile int value_pro = 0;


//TINH toan ra TMR0 = 131
//nhung de TMR0=135 thi mo phong oke hon
void timer()
{
    PS0 = 1;//:16
    PS1 = 1;
    PS2 = 0;
    
    PSA = 0;
    
    T0SE = 0;
    
    T0CS = 0;//using crytal
    
    TMR0IE = 1;
    TMR0IF = 0;
    GIE = 1;
    
    TMR0 = 135;
}

void __interrupt() ISR()//NGAT 10 ms 1 lan
{
    if(TMR0IE && TMR0IF)
    {
        
        value_10++;
        if(value_10 == 10)//1ms*10 = 10ms
        {
            value_10 = 0;
            LED = ~LED;
        }
        
        value_5++;
        if(value_5 == 5)
        {
            value_5 = 0;
            LED_1 = ~LED_1;
        }
        
        value_pro++;
        if(value_pro == 10)
            value_pro=0;
        if(value_pro<=3)
            LED2=1;
        else
            LED2=0;
            
         
        TMR0 = 135;
        TMR0IF = 0;
    }
}
void main(void)
{
    ADCON1 = 0x07;
    
    TRIS_LED = 0;// AS OUTPUT
    LED = 0;
    
    TRIS_LED_1 = 0;
    LED_1 = 0;
    
    TRIS_LED2 = 0;
    LED2=0;
    
    timer();
    while(1)
    {
        //LED = !LED;
    }
    return;
}
