/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 24 November, 2021, 10:46 AM
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

unsigned int dem = 0,nghin,tram,chuc,donvi;

unsigned char maled[10]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};


void counter1()
{
    T1CONbits.TMR1CS = 1;//Ch?n ngu?n xung clock t? bên ngoài ? chân RC0/T1OSO/T1CKI (c?nh lên).
    T1CONbits.T1SYNC = 0;//??ng b? ngõ vào clock ? t? bên ngoài.
    T1CONbits.TMR1ON = 1;// Cho phép Timer1 ??m.
}

void display()
{
    nghin = dem/1000;
    tram = (dem - nghin*1000)/100;
    chuc = (dem - nghin*1000 - tram*100)/10;
    donvi = dem - nghin*1000 - tram*100 - chuc*10;
    
    PORTB = maled[nghin];
    RD0=0;
    __delay_ms(5);
    RD0=1;
    
    PORTB = maled[tram];
    RD1=0;
    __delay_ms(5);
    RD1=1;

    PORTB = maled[chuc];
    RD2=0;
    __delay_ms(5);
    RD2=1;

    PORTB = maled[donvi];
    RD3=0;
    __delay_ms(5);
    RD3=1;
}

void main(void) 
{
    ADCON1=0x06;
    
    TRISB = 0;
    PORTB = 0;
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    PORTD = 0;
    
    counter1();
    while(1)
    {
        display();
        dem=TMR1;
        if(dem>=1500)
        {
            TMR1=0;
            dem=0;
        }
    }
    return;
}
