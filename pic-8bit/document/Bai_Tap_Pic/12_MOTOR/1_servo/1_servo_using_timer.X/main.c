/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 26 November, 2021, 4:34 AM
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

int degree=-1;
int count = 0;
int count_s = 5;
int value=0;

void servoRotate0();
void servoRotate90();
void servoRotate180();
void roundDegree();
/*
    Delay Calculations for 0.1ms @20Mhz with Prescalar as 32:
    RegValue = 256-(Delay * Fosc)/(Prescalar*4))	//s , Hz
    = 256-((1ms * 20Mhz)/(32*4)) = 256-16=240
 
 */
//tinh toan dcTMR0=240 nhung TMR0=241 ok hon
void timer0()
{
    PS2=1; PS1=0; PS0=0;//1 : 32
    
    PSA=0;
    T0SE=0;
    T0CS=0;
    
    GIE=1; //Enable Global Interrupt
    
    TMR0=241;       // Load the time value for 0.1 ms delay
    
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
}

void change()
{
    RBIE=1;
    RBIF=0;
    GIE=1;
}

void __interrupt() time()
{
    if(RBIE && RBIF)
    {
        if(!RB4)
            degree = 0;
        if(!RB5)
            degree = 90;
        if(!RB6)
            degree = 180;
        RBIF=0;
    }
    
    if(TMR0IE&&TMR0IF)
    {
        count++;
        if(count>=200)// 20 ms
        {
            count=0;
            
            
            value++;
            if(value >= 50)//1 s
            {
                value=0;
                count_s++;
                if(count_s >= 20)
                    count_s = 5;
            }
        }
        
        TMR0 = 241; /*Load the timer Value, (Note: Timer value is 101 instaed of 100 as the
                    TImer0 needs two instruction Cycles to start incrementing TMR0) */
        TMR0IF=0; // Clear timer interrupt flag
    }
}

void main(void) 
{
    ADCON1=0x06;
    TRISD7=0;
    
    timer0();
    change();
    
    while(1)
    {
        /*
        if(degree == 0)
          servoRotate0(); //0 Degree
        if(degree == 90)
          servoRotate90(); //90 Degree
        if(degree == 180)
          servoRotate180(); //180 Degree
        */
        roundDegree();
    }
    
    return;
}

void servoRotate0()//0 Degree
{
    if(count<5)
        RD7 = 1;
    else
        RD7 = 0;
}

void servoRotate90()//90 degree
{
    if(count<14)
        RD7 = 1;
    else
        RD7 = 0;
}

void servoRotate180()//180 degree
{
    if(count<25)
        RD7 = 1;
    else
        RD7 = 0;
}

//quay 0 -> 180 -> 0
void roundDegree()
{    
    for(int m = 0; m <= 50; m++)
    {
        if(count <= count_s)
            RD7 = 1;
        else  if(count > count_s)
            RD7 = 0;
    }
}