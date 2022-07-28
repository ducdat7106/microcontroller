/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 30 November, 2021, 10:02 AM
 */

//#define _XTAL_FREQ 16000000

#include<stdio.h>
#include <xc.h>
#include<stdint.h>
#include<string.h>

#include"config.h"
#include"adc_thay_hai.h"
#include"uart.h"
#include"lcd_hd44780_pic16.h"

#define led PORTEbits.RE2
#define tris_led TRISEbits.TRISE2

unsigned int i=0;
unsigned int count, count1, count_s;
unsigned char do_dienap=0;
unsigned char adc_ok;
float dong, dienap;

char in_buffer[6];
unsigned char in_count;
unsigned char check_sang;


char commbuffer[10];
char str[50];
unsigned int a=10;

//=============================================================================
//===================start function=============================================

void TIMER1_Init();
void UART_Write_data(unsigned char Value);
void display();

//===================finish function===========================================
//=============================================================================

void __interrupt() ISR()    //1ms
{
    char ch;
    
    if(TMR1IE && TMR1IF)
    {
        TMR1 = 65036;
        TMR1IF=0;
        
        count++;
        if(count == 20) //20ms
        {
            count++;
            count1++;
            if(do_dienap)
            {
                dienap=(float)ADC_Read(0);
                dienap *= 0.489;
                adc_ok=1;
            }
            else
            {
                dong=(float)ADC_Read(1);
                dong*=0.0978;
                adc_ok=1;
            }
            
            do_dienap =~ do_dienap;
        }
    }
    
    if(RCIE && RCIF)
    {
        ch=RCREG;
        if(check_sang)
            in_buffer[in_count++]=ch;
        
        if(in_count == 6)
        {
            in_count=0;
            check_sang=0;
        }
        
        if(ch == '{')
        {
            in_count=0;
            check_sang=1;
        }
        
        if(ch == '}')
        {
            check_sang = 0;
            if(strncmp(in_buffer, "Sang", 4)==0)
                led=0;
            if(strncmp(in_buffer, "Tat", 3)==0)
                led=1;
        }
    }
}


void main(void) 
{
   unsigned char digit[3] = {0, 0, 0};
    unsigned int adc_value = 0;
    
    
    //ADCON1=0x06;
    tris_led =0;
    led=0;
    ADC_Init();
    TIMER1_Init(); 
    
    LCDInit(LS_NONE);
    LCDClear();
    
    UART_Init(9600);
    
    LCDGotoXY(0,0);
    LCDWriteString("Do U/I....");
    __delay_ms(1000);
    LCDClear();
    
    while(1)
    {
      // LCDGotoXY(0,0);
       //LCDData(5  + 0x30);
        //display();
        if(adc_ok && count1==25)
    {
        count1=0;
        adc_value = (unsigned int)dong;
        digit[2] = adc_value/100;
        digit[1] = (adc_value%100)/10;
        digit[1] = (adc_value%100)%10;
        UART_Write_data(adc_value);
        
        LCDGotoXY(0, 1);
        LCDWriteString("I= ");
        LCDData(digit[2]+0x30);
        LCDData('.');
        LCDData(digit[1]+0x30);
        LCDData(digit[0]+0x30);
        
        adc_value = (unsigned int)dienap;
        digit[2] = adc_value/100;
        digit[1] = (adc_value%100)/10;
        digit[1] = (adc_value%100)%10;
        UART_Write_data(adc_value);
        
        LCDGotoXY(0, 1);
        LCDWriteString("U= ");
        LCDData(digit[2]+0x30);
        LCDData('.');
        LCDData(digit[1]+0x30);
        LCDData(digit[0]+0x30);
    }
        
    }
    return;
}

/*
 1 m s  have once interrupt

 */
void TIMER1_Init()
{
    TMR1ON=1;//enable timer 2
    
    TMR1CS=0;//Fosc/4
    
    T1SYNC=1;
    
    T1OSCEN=0;

    T1CKPS0 = 1;//1:8
    T1CKPS1 = 1;
    
    TMR1 = 65036;
    TMR1IE=1;
    TMR1IF=0;
    GIE=1;
    PEIE=1;
}

void UART_Write_data(unsigned char Value)
{
    unsigned char i;
    unsigned int k;
    
	commbuffer[0]='{';    
	commbuffer[1]=Value/100+0x30; //'1';
    commbuffer[2]='.';
    k=Value%100;
	commbuffer[3]=k/10+0x30;
	commbuffer[4]=k%10+0x30;
	commbuffer[5]='}';
    commbuffer[6]='\r';//0x0d;
    
   for(i=0;i<7;i++)
    {
      TXREG=commbuffer[i];
      while(TRMT==0);      
    }
}

void display()
{
    unsigned char digit[3] = {0, 0, 0};
    unsigned int adc_value = 0;
    
    if(adc_ok && count1==25)
    {
        count1=0;
        adc_value = (unsigned int)dong;
        digit[2] = adc_value/100;
        digit[1] = (adc_value%100)/10;
        digit[1] = (adc_value%100)%10;
        UART_Write_data(adc_value);
        
        LCDGotoXY(0, 1);
        LCDWriteString("I= ");
        LCDData(digit[2]+0x30);
        LCDData('.');
        LCDData(digit[1]+0x30);
        LCDData(digit[0]+0x30);
        
        adc_value = (unsigned int)dienap;
        digit[2] = adc_value/100;
        digit[1] = (adc_value%100)/10;
        digit[1] = (adc_value%100)%10;
        UART_Write_data(adc_value);
        
        LCDGotoXY(0, 1);
        LCDWriteString("U= ");
        LCDData(digit[2]+0x30);
        LCDData('.');
        LCDData(digit[1]+0x30);
        LCDData(digit[0]+0x30);
    }
}