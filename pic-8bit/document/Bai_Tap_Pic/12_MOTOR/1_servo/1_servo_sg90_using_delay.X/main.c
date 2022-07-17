/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 26 November, 2021, 3:48 AM
 */
#define _XTAL_FREQ 8000000

#include <xc.h>

// BEGIN CONFIG
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON 
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF 
#pragma config CP = OFF
//END CONFIG

int degree=-1;
void servoRotate0() //0 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD7 = 1;
    __delay_us(500);
    RD7 = 0;
    __delay_us(19500);
  }
}

void servoRotate90() //90 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD7 = 1;
    __delay_us(1500);
    RD7 = 0;
    __delay_us(18500);
  }
}

void servoRotate180() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD7 = 1;
    __delay_us(2500);
    RD7 = 0;
    __delay_us(17500);
  }
}
void change()
{
    RBIE=1;
    RBIF=0;
    GIE=1;
}

void __interrupt() portB()
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
}
void main()
{
    ADCON1=0x06;
   
    TRISD7 = 0; // RD7 as Ouput Port
    
    change();
    
    do
    {
        if(degree == 0)
          servoRotate0(); //0 Degree
        if(degree == 90)
          servoRotate90(); //90 Degree
        if(degree == 180)
          servoRotate180(); //180 Degree
    }while(1);
}
