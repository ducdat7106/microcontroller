/*
 * File:   main_muti_adc.c
 * Author: Nguyen Duc Dat
 *
 * Created on 5 December, 2021, 3:31 AM
 */


#include <xc.h>
#include"ADC_internet.h"
#include"config.h"

#define led7seg PORTB
#define tris_led7seg TRISB

#define led1_1 PORTCbits.RC0
#define led1_2 PORTCbits.RC1

#define led2_1 PORTCbits.RC2
#define led2_2 PORTCbits.RC3

#define led3_1 PORTCbits.RC4
#define led3_2 PORTCbits.RC5

#define tris_led1_1 TRISCbits.TRISC0
#define tris_led1_2 TRISCbits.TRISC1

#define tris_led2_1 TRISCbits.TRISC2
#define tris_led2_2 TRISCbits.TRISC3

#define tris_led3_1 TRISCbits.TRISC4
#define tris_led3_2 TRISCbits.TRISC5

unsigned char number[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

unsigned int donvi, chuc;
unsigned int value1, value2, value3;
float Temp;

void hienThi()
{
    led7seg=0xff;
    
    donvi = value1/10;
    chuc = value1%10;
    led1_1=1;led1_2=0;
    led7seg = number[donvi];
    __delay_ms(2);
    led1_1=0;led1_2=1;
    led7seg = number[chuc];
    __delay_ms(2);
    led1_2=0;
    
    donvi = value2/10;
    chuc = value2%10;
    led2_1=1;led2_2=0;
    led7seg = number[donvi];
    __delay_ms(2);
    led2_1=0;led2_2=1;
    led7seg = number[chuc];
    __delay_ms(2);
    led2_2=0;
    
    donvi = value3/10;
    chuc = value3%10;
    led3_1=1;led3_2=0;
    led7seg = number[donvi];
    __delay_ms(2);
    led3_1=0;led3_2=1;
    led7seg = number[chuc];
    __delay_ms(2);
    led3_2=0;
}

void docAdc()
{
    value1=ADC_Read(0);
    value1 = (unsigned int)( (value1*50)/1023 );
    
    value2=ADC_Read(1);
    value2 = (unsigned int)( (value2*50)/1023 );
    
    value3=ADC_Read(2);
    value3 = (unsigned int)( (value3*50)/1023 );
}

void main(void)
{
    unsigned int i=0;
    tris_led7seg = 0x00;
    
    tris_led1_1=0;
    tris_led1_2=0;
    
    tris_led2_1=0;
    tris_led2_2=0;
    
    tris_led3_1=0;
    tris_led3_2=0;
    
    ADC_Init();
    
    while(1)
    {
        i++;
        if(i >= 25)//tre
        {
            i=0;
            docAdc();
        }
        
        hienThi();
    }
    
    return;
}
