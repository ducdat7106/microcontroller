/*
 * File: PWM_POT_HG.c
 * Author: Dell
 * my blog http://xcvn.blogspot.com
 * Created on November 21, 2015, 10:10 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "PWM.h"
#define _XTAL_FREQ 4000000
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
void PWM(void);
void ADCinit (void);
unsigned int ReadADC (void);
unsigned int ADCvalue = 0;
unsigned int duty=0;
void main(void) 
{
    ADCinit();
    PWM();
    while(1)
    {
        ADCvalue = ReadADC();
        duty = (ADCvalue/1023.0)*100.0;//while
        PWM1_Duty(duty);        
    }
}
void PWM(void)//ham khai bao pwm
{
    PWM1_Init_Fre(1000);
    PWM1_Duty(duty);//while
    PWM1_Start();
}
void ADCinit (void)// adc
{
    // chon tan so clock cho bo adc
    ADCON1bits.ADCS2 = 0, ADCON0bits.ADCS1 = 0,ADCON0bits.ADCS0 = 1;
    // chon kenh adc la kenh an0
    ADCON0bits.CHS2 = 0, ADCON0bits.CHS1 = 0, ADCON0bits.CHS0 = 0;
    // chon cach luu data
    ADCON1bits.ADFM = 1;
    // cau hinh cong vao
    ADCON1bits.PCFG3 = 1,  ADCON1bits.PCFG2 = 1,  ADCON1bits.PCFG1 = 1,  ADCON1bits.PCFG0 = 0;
    // cap nguon cho khoi adc
    ADCON0bits.ADON = 1;
}
unsigned int ReadADC (void)// doc len 7 doan
{
    unsigned int TempValue = 0;
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);
    TempValue = ADRESH*256 + ADRESL;
    return (TempValue);
}