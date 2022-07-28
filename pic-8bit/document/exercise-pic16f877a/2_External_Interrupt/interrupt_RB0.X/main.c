/*
 * File:   main.c
 * Author: Dat Nguyen
 * Created on 22 November, 2021, 4:58 AM
 */
#include <xc.h>
#include"config.h"
#include"lcd.h"

#define LED PORTEbits.RE2
#define tris_LED TRISEbits.TRISE2
//#define _XTAL_FREQ 16000000

unsigned int number=0;
unsigned char Digit[]={0,0,0,0};

void ExtInt()
{
    //OPTION_REG = 0b00000000;  // Enables PULL UPs -> no need res external
    INTE=1;
    GIE=1;
}

void __interrupt() ISR()
{
    if(INTE&&INTF)
    {
        INTF=0;// clear the interrupt flag after done with it
        LED=~LED;
        number++;
        if(number>10)
            number=1;
    }
}



void main(void) 
{
    ADCON1=0x07;
    tris_LED=0;
    LED=1;
    
    unsigned int k=0, i=0;
    
    ExtInt();
     
    LCD_Init();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("RUN....");
    __delay_ms(1000);
    //LCD_Clear();
    LCD_Set_Cursor(2,1);
    LCD_Write_String("Counter: ");
    __delay_ms(1000);
    
    while(1)
    {
        Digit[0]=number/1000;
        k=number%1000;
        Digit[1]=k/100;
        k=k%100;
        Digit[2]=k/10;
        Digit[3]=k%10;
        
        LCD_Set_Cursor(2,10);
        for(i=0; i<4; i++)
            LCD_Write_Char(Digit[i]+0x30);
        __delay_ms(1000);
        LCD_Write_String("...");
          
    }
    return;
}
