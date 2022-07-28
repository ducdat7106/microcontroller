/*
 * File:   main_do_tan-so.c
 * Author: Dat Nguyen
 *
 * Created on 27 November, 2021, 4:03 PM
 */


#include <xc.h>
#include"lcd.h"

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

unsigned int u32NumberOfCounterOver=0;
unsigned int NumberOfTick=0;
float fFrequency = 0;
char str[30];

void timer1_config()
{
    GIE=1;
    PEIE=1;
    TMR1IE=1;
    TMR1IF=0;
    
    TMR1CS=0;// internal clock(Fosc/4) --> ko phai dem xung
    
    T1CKPS0=0;//1:1
    T1CKPS1=0;
}

//ko can xac dinh thoi gian bao lau xay ra 1 ngat
void __interrupt(high_priority) ISR()
{
    if(TMR1IE && TMR1IF)
    {
        u32NumberOfCounterOver++;
        TMR1IF=0;
    }
}


void main(void) 
{
    ADCON1=0x06;
    
    TRISB0=1;
    TRISC=0;
    TRISD=0;
    
    LCD_Init();
    LCD_Clear();
    LCD_Set_Cursor(1,1);
    timer1_config();
    while(1)
    {
        TMR1H=0;//xoa gia tri TIMER1
        TMR1L=0;
        while(RB0==1);
        while(RB0==0);
        TMR1ON=1;
        while(RB0==1);
        while(RB0==0);
        TMR1ON=0;
        
        NumberOfTick = (TMR1H<<8) | TMR1L;
        
        //1 tick = 1/5M  -->T=NumberOfTick/5M  -->f=5M/NumberOfTick
        
        
        /* 
                          1
    Fxung  = -------------------------------- (Hz)
                 1
             ----------  X  (Tong so lenh)         
             5 000 000
          
         */
        
        
        
        fFrequency = 5000000.0/(NumberOfTick+u32NumberOfCounterOver*65536);
        
        sprintf(&str[0], "%f", fFrequency);
        LCD_Set_Cursor(1,1);
        LCD_Write_String(&str[0]);
        
        u32NumberOfCounterOver = 0;
    }
    return;
}
