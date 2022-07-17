/*
 * File:   main controller motor.c
 * Author: Nguyen Duc Dat
 *
 * Created on 16 December, 2021, 1:00 AM
 */


#include <xc.h>
#include <proc/pic16f877a.h>
#include"config.h"
#include"pwm.h"

#define P1_UP PORTDbits.RD0
#define P1_DOWN PORTDbits.RD1
#define P2_UP PORTDbits.RD2
#define P2_DOWN PORTDbits.RD3

#define TRIS_P1_UP TRISDbits.TRISD0
#define TRIS_P1_DOWN TRISDbits.TRISD1
#define TRIS_P2_UP TRISDbits.TRISD2
#define TRIS_P2_DOWN TRISDbits.TRISD3

unsigned int value1=0;
unsigned int value2=0; 
    
void main(void) 
{
    ADCON1 = 0x07;

    TRIS_P1_DOWN =1;
    TRIS_P1_UP = 1;
    TRIS_P2_UP = 1;
    TRIS_P2_DOWN = 1;
    
    TRISB0=0;
    RB0=0;
    
    PWM1_Init(5000);//f=5000 Hz
    PWM1_Start();
    
    PWM2_Init(5000);
    PWM2_Start();
    
    PWM1_Set_Duty(value1);
    PWM2_Set_Duty(value2);  //0%-100%
    while(1)
    {
        
        //dieu khien dong co 1
        if(P1_UP == 0)
        {
            while(P1_UP == 0);
            RB0=1;
            value1=value1+10;
            if(value1 > 100)
                value1 = 100;
        }
        
        if(P1_DOWN == 0)
        {
            while(P1_DOWN == 0);
            RB0=1;
            value1=value1-10;
            if(value1 <= 0)
                value1=0;
            
        }
        
        //dieu khen dong co 2
         if(P2_UP == 0)
        {         
            while(P2_UP == 0);
            RB0=1;
            value2=value2+10;
            if(value2 >= 100)
                value2 = 100;
        }
        
        if(P2_DOWN == 0)
        {
            while(P2_DOWN == 0);
            RB0=1;
            value2=value2-10;
            if(value2 <= 0)
                value2=0;
            
        }
        RB0=0;
        
        PWM1_Set_Duty(value1);
        PWM2_Set_Duty(value2);  //0%-100%
        
    }
    return;
}
