/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 24 November, 2021, 9:44 AM
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

unsigned int dem = 0,nghin,tram,chuc,donvi;

unsigned char number[10]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};


void couter0()
{
    OPTION_REGbits.T0CS = 1;          // Dem xung ngoai
    OPTION_REGbits.PSA = 1;           // Su dung bo chia truoc WDT
    T0SE = 1;// Increment on high-to-low transition on T0CKI pin
}

void display (void)
{
    chuc = dem/10;
    donvi = dem%10;
    
    PORTB = number[chuc];
    RC0=0;
    __delay_ms(10);
    RC0=1;
    
    PORTB = number[donvi];
    RC1=0;
    __delay_ms(10);
    RC1=1;
}

void main(void) 
{
    ADCON1=0x06;
    
    TRISB = 0;
    PORTB = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    RC0=RC1=0;
    
    couter0();
    while(1)
    {
        display();
        dem=TMR0;
        if(dem>=100)
        {
            TMR0=0;
            dem=0;
        }
    }
    return;
}
