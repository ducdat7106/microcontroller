/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 24 November, 2021, 5:26 PM
 */
#include <xc.h>
#include <stdint.h>
#include "adc.h"
#include "config.h"
//#define _XTAL_FREQ 20000000
unsigned char seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xCE, 0x80, 0x90};

//***Define the signal pins of all four displays***//
#define s1 RC0
#define s2 RC1
#define s3 RC2
#define s4 RC3
//***End of definition**////

void main(void) 
{
    int a,b,c,d,e,f,g,h,adc; //just variables
    unsigned int i = 0; //the 4-digit value that is to be displayed
    int flag =0; //for creating delay
    
    //*****I/O Configuration****//
    TRISC=0X00;
    PORTC=0X00;
    TRISD=0x00;
    PORTD=0X00;
    
    TRISC7=0;
    RC7=0;
    //***End of I/O configuration**///
    
    ADC_Initialize();
    
    while(1)
    {
        //RA0=~RA0;
         if(flag>=50) //wait till flag reaches 100
        {
             RC7=~RC7;
             adc = ADC_Read(2);
             i = (unsigned int)(adc*0.488281);//dien ap
             
             flag=0; //only if flag is hundred "i" will get the ADC value
        }
        flag++; //increment flag for each flash
        
        //***Splitting "i" into four digits***//  
        a=i%10;//4th digit is saved here
        b=i/10;
        c=b%10;//3rd digit is saved here
        d=b/10;
        e=d%10; //2nd digit is saved here
        f=d/10;
        g=f%10; //1st digit is saved here
        h=f/10;
        //***End of splitting***//
        
        PORTD=seg[g];s1=1; //Turn ON display 1 and print 4th digit
        __delay_ms(5);s1=0;     //Turn OFF display 1 after 5ms delay
        PORTD=seg[e];RD7=1;s2=1; //Turn ON display 2 and print 3rd digit
        __delay_ms(5);s2=0;     //Turn OFF display 2 after 5ms delay
        PORTD=seg[c];s3=1; //Turn ON display 3 and print 2nd digit
        __delay_ms(5);s3=0;     //Turn OFF display 3 after 5ms delay
        PORTD=seg[a];s4=1; //Turn ON display 4 and print 1st digit
        __delay_ms(5);s4=0;     //Turn OFF display 4 after 5ms delay
    }
    return;
}
