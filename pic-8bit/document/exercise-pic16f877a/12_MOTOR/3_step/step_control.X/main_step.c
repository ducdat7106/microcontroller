/*
 * File:   main_step.c
 * Author: Dat Nguyen
 *
 * Created on 25 November, 2021, 4:10 PM
 */
#pragma config FOSC = XT // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
 
#define _XTAL_FREQ 4000000

#include <xc.h>
#include "step_motor.h"
#include "adc.h"

#define button_forword_rotation PORTBbits.RB4
#define button_reverse_rotation PORTBbits.RB5   //xoay nguoc
#define button_start            PORTBbits.RB6
#define button_stop             PORTBbits.RB7

#define tris_button_forword_rotation    TRISBbits.TRISB4
#define tris_button_reverse_rotation    TRISBbits.TRISB5
#define tris_button_start               TRISBbits.TRISB6
#define tris_button_stop                TRISBbits.TRISB7

int mode;         //1 = forward ; 0 = reverse
int ready;        //1 = stop ; 0 = start
int dummy;

void Config_Init();

void delay_ms(unsigned int );

void External_Interrup_PortB(){
    RBIE=1;
    GIE=1;
}

//Interrupt Service Routine
void __interrupt() isr(void){
    if(RBIF && RBIE)
    {           //check RB change interrupt flag if triggered
      dummy = PORTB;    //read PORTB to clear mismatch condition
      if(!button_stop)
      {         //stop button pressed?
          ready = 1;
      }else if(!button_start)
      {   //start button pressed?
          ready = 0;
      }else if(!button_reverse_rotation)
      {   //reverse button pressed?
          mode = 0;
      }else if(!button_forword_rotation)
      {   //forward button pressed?
          mode = 1;
      }else{;}
    }
    RBIF = 0;
}


//Main Routine
void main(void) {
    
    Config_Init();    
    
    while(1){
        if(ready==0)
        {
            if(mode==1){          
               // Wave_Drive_Mode(0);
                Full_Drive_Mode(0, 100);
                //Half_Drive_Mode(0);
            } else if(mode==0){    
               // Wave_Drive_Mode(1);
                Full_Drive_Mode(1, 100);
                //Half_Drive_Mode(1);
                
            }
      }
    }
    return;
}
 

void Config_Init(){
    ADCON1 = 0x06;
    
    External_Interrup_PortB();
    
    Step_Motor_Init();
    
    ready = 1;       //motor is stopped by default;
}


