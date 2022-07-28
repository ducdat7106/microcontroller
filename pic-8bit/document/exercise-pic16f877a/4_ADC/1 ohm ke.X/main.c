/*
 * File:   main.c
 * Author: Nguyen Duc Dat
 *
 * Created on 1 December, 2021, 5:48 AM
 */
#include <xc.h>
#include<stdint.h>

#include"adc_thay_hai.h"
#include"config.h"
#include"lcd_hd44780_pic16.h"

//#define _XTAL_FREQ 16000000

#define led PORTBbits.RB0
#define tris_led TRISBbits.TRISB0

unsigned char count=0, count1=0;
unsigned int value_adc=0;
unsigned int resister=0;

unsigned char adc_ok=0;
float dienap=0;

void Init_uart(void);
void Send_data(unsigned int Value);

void TIMER1_Init()
{
    TMR1ON=1;
    TMR1CS=0;
    T1SYNC=0;
    T1OSCEN=0;
    T1CKPS1=1;
    T1CKPS0=1;  //1:8
    
    TMR1IE=1;
    TMR1IF=0;
    PEIE=1;
    GIE=1;
    
    TMR1=65036;
}

void __interrupt() ISR()//1 m s
{
    if(TMR1IE && TMR1IF)
    {
        count++;
        if(count>20)//20 m s
        {
            count=0;
            count1++;
            dienap=(float)ADC_Read(0);
            dienap*=0.48828;// dien a p (V))
            adc_ok=1;
        }
        
        led=~led;
        
        TMR1=65036;
        TMR1IF=0;
    }
}


void main(void) 
{
    unsigned char digit[4]={0,0,0};
    unsigned int value;
    tris_led=0;
    led=1;
    
    ADC_Init();
    Init_uart();
    LCDInit(LS_NONE);
    LCDGotoXY(0,0);
    LCDWriteString("load resister...");
    __delay_ms(1000);
    LCDClear();
    
    TIMER1_Init();
    
    while(1)
    {
        
        if(adc_ok == 1 && count1 >= 25)
        {
            count1=0;
            
            value=(unsigned int)dienap;
            digit[2] = value/100;
            digit[1] = (value%100)/10;
            digit[0] = value%10;
            
           
            LCDGotoXY(0,0);
            LCDWriteString("G tri U= ");
            LCDData(digit[2]+0x30);
            LCDData('.');						// Display first digit
            LCDData(digit[1]+0x30);								// Display second digit
            LCDData(digit[0]+0x30);	
            
            resister=(unsigned int)( (10000*dienap/100)/(5-dienap/100) );
            Send_data(resister);
            
            LCDGotoXY(0,1);
            LCDWriteInt(resister, 8);
            
           
        }
         
         
    }
    return;
}

