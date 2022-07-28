/*
 * File:   main dem sp.c
 * Author: Nguyen Duc Dat
 *
 * Created on 19 December, 2021, 1:26 PM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

///_XTAL_FREQ = 8000000
#include <xc.h>

#define COUNT1 PORTBbits.RB4
#define COUNT2 PORTBbits.RB5
#define RESET1 PORTBbits.RB6
#define RESET2 PORTBbits.RB7    

#define LED PORTCbits.RC7
#define TRIS_LED TRISCbits.TRISC7

#define LED_7SEG PORTD
#define TRIS_LED_7SEG TRISD

#define EN1 PORTAbits.RA0
#define EN2 PORTAbits.RA1
#define EN3 PORTAbits.RA2
#define EN4 PORTEbits.RE0
#define EN5 PORTEbits.RE1

#define TRISEN1 TRISAbits.TRISA0
#define TRISEN2 TRISAbits.TRISA1
#define TRISEN3 TRISAbits.TRISA2
#define TRISEN4 TRISEbits.TRISE0
#define TRISEN5 TRISEbits.TRISE1

unsigned char number[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned int value1=0, value2=0;
unsigned int timeNho=0, timeLon=0;
unsigned int counts=0;

int nghin1, tram1, chuc1, donvi1;
int nghin2, tram2, chuc2, donvi2;

void numbers(unsigned int value, int *nghin, int *tram, int *chuc, int *donvi);
void DisplayLed7Seg(int nghin, int tram, int chuc, int donvi, int viTri);


void external_interrupt()
{
    RBIE=1;
    RBIF=0;
    GIE=1;
}

void time0()//1 ms
{
    PS2=1; PS1=0; PS0=0;//1 : 32
    
    PSA=0;
    T0SE=0;
    T0CS=0;
    
    GIE=1; //Enable Global Interrupt
    
    TMR0=100;       // Load the time value for 1ms delay
    
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    TMR0IF =0;
}

void __interrupt() ISR()
{
    if(RBIE && RBIF)
    {
        if(COUNT1 == 0)
        {
            //while(COUNT1 == 0);
            value1++;
            if(value1>9999)
                value1=0;
        }
        
        if(COUNT2 == 0)
        {
            //while(COUNT2 == 0);
            value2++;
            if(value2>9999)
                value2=0;
        }
        
        if(RESET1 == 0)
        {
            //while(RESET1==0);
            value1 =0;
        }
        
        if(RESET2 == 0)
        {
            //while(RESET2 == 0)
            value2=0;
        }
        RBIF=0;
    }
    
    if(TMR0IE && TMR0IF)
    {
        //truong hop 1
        if((value1==value2) && (value2==0))
            LED=0;//tat
        
        //truong hop 2
        if((value1==value2) && (value2>0))
            LED=1;//bat
        
        //truong hop 3
        timeNho++;
        if(timeNho>=1000)
            timeNho=0;
        if(value1<value2)
        {
            if(timeNho<500)
                LED=1;
            else
                LED=0;
        }
        
        //truong hop 4
        timeLon++;
        if(timeLon>=2000)
            timeLon=0;
        if(value1>value2)
        {
            if(timeLon<500)
                LED=1;
            else
                LED=0;
        }
        
        
        TMR0=100;
        TMR0IF=0;
    }
}


//viTri = 1,2
void DisplayLed7Seg(int nghin, int tram, int chuc, int donvi, int viTri)
{
    LED_7SEG = 0xff;
    EN5=0;EN1=1;EN2=1;EN3=1;EN4=1;
    LED_7SEG = number[viTri];
    __delay_ms(2);
    
    LED_7SEG = 0xff;
    EN5=1;EN1=0;EN2=1;EN3=1;EN4=1;
    LED_7SEG = number[nghin];
    __delay_ms(2);
    
    LED_7SEG = 0xff;
    EN5=1;EN1=1;EN2=0;EN3=1;EN4=1;
    LED_7SEG = number[tram];
    __delay_ms(2);
    
    LED_7SEG = 0xff;
    EN5=1;EN1=1;EN2=1;EN3=0;EN4=1;
    LED_7SEG = number[chuc];
    __delay_ms(2);
    
    LED_7SEG = 0xff;
    EN5=1;EN1=1;EN2=1;EN3=1;EN4=0;
    LED_7SEG = number[donvi];
    __delay_ms(2);
}


void numbers(unsigned int value, int *nghin, int *tram, int *chuc, int *donvi)
{
    unsigned int temp=0;
    *nghin = value/1000;
    temp=value%1000;
    *tram =  temp/100;
    temp=temp%100;
    *chuc = temp/10;
    *donvi = temp%10;
}


void main(void)
{
    ADCON1 = 0x06;
    
    int count_s=0;
    
    TRIS_LED_7SEG = 0x00;
    LED_7SEG = 0xFF;
    
    TRIS_LED = 0;
    LED = 0;
    
    TRISEN1 =0; TRISEN2 =0; TRISEN3 =0; TRISEN4 =0; TRISEN5 = 0;
    EN1 =  EN2 = EN3 = EN4 = EN5 = 1;
    
    external_interrupt();
    time0();
    
   
    while(1)
    {
        numbers(value1, &nghin1, &tram1, &chuc1, &donvi1);
        numbers(value2, &nghin2, &tram2, &chuc2, &donvi2);
        count_s++;
        if(count_s == 100)
        {
            count_s=0;
        }
        
        if(count_s<50)
            DisplayLed7Seg(nghin1, tram1, chuc1, donvi1, 1);
        else
            DisplayLed7Seg(nghin2, tram2, chuc2, donvi2, 2);
    }
    return;
}
