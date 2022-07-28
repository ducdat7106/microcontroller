/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 25 November, 2021, 5:32 AM
 */

#include <xc.h>
#include"adc_thay_hai.h"
#include"pwm.h"

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

unsigned char seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xCE, 0x80, 0x90};

//***Define the signal pins of all four displays***//
#define s1 RD0
#define s2 RD1
#define s3 RD2
#define s4 RD3
//***End of definition**////


void main(void)
{
    //unsigned int adc=0;
    unsigned int i=0;
    int a,b,c,d,e,f,g,h,adc; //just variables
    //unsigned int i = 0; //the 4-digit value that is to be displayed
    
    TRISB=0X00;
    PORTB=0X00;
    TRISD=0x00;
    PORTD=0X00;
    
    ADC_Init();
    PWM1_Init(5000);
    PWM1_Start();
    while(1)
    {
        adc=ADC_Read(0);
        i=adc;
        PWM1_Set_Duty(i);
        
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
        
        PORTB=seg[g];s1=1; //Turn ON display 1 and print 4th digit
        __delay_ms(5);s1=0;     //Turn OFF display 1 after 5ms delay
        PORTB=seg[e];RD7=1;s2=1; //Turn ON display 2 and print 3rd digit
        __delay_ms(5);s2=0;     //Turn OFF display 2 after 5ms delay
        PORTB=seg[c];s3=1; //Turn ON display 3 and print 2nd digit
        __delay_ms(5);s3=0;     //Turn OFF display 3 after 5ms delay
        PORTB=seg[a];s4=1; //Turn ON display 4 and print 1st digit
        __delay_ms(5);s4=0;     //Turn OFF display 4 after 5ms delay
    }
    return;
}
