/*
 * File:   main.c
 * Author: NGUYEN DUC DAT
 *
 * Created on 3 January, 2022, 3:08 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000

#include <xc.h>
#include"adc.h"
#include"lcd.h"

// Servo definition and variables
#define MAX_VALUE 200   //0.1 ms * 200 = 20 ms
#define CCW_ROTATION MAX_VALUE - 20
#define CW_ROTATION MAX_VALUE - 10
#define STOP_ROTATION MAX_VALUE
#define THRESHOLD_VALUE 50  //gia tri nguong

unsigned char pulse_max = 0;//xung toi da
unsigned char pulse_top = 0;//dinh xung
unsigned char top_value = 0;//gia tri dinh
/*

top_value = MAX_VALUE;     // Stop the Servo Motor
top_value = CCW_ROTATION;  // Counterclockwise Rotation
top_value = CW_ROTATION;   // Clockwise Rotation
 
 */


void timer0()//0.1 ms
{
    PS2=1; PS1=0; PS0=0;//1 : 32
    
    PSA=0;
    T0SE=0;
    T0CS=0;
    
    GIE=1; //Enable Global Interrupt
    
    TMR0=242;       // Load the time value for 1ms delay
    
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
}

void __interrupt() isr()//0.1 ms
{
  if(TMR0IE&&TMR0IF) // TIMER0 Interrupt Flag
  {	            
    pulse_max++;            // Pulse Max Increment
    pulse_top++;            // Pulse Top Increment

    /* MAX_VALUE=200 turn off the pulse */
    if (pulse_max >= MAX_VALUE) 
    {
      pulse_max=0;
      pulse_top=0;
      RC2=0;                // Turn off RC2
    }

    /* top_value = MAX_VALUE - n, n=10: 10 x 0.1ms = 1.0ms, n=20: 20 x 0.1ms = 2.0ms */
    /* 2ms -> CCW Rotation, 1ms -> CW Rotation */
    if (pulse_top == top_value) 
    {
      RC2=1;                // Turn On RC2
    }
    
    TMR0 = 242;             // Initial Value for 0.1ms Interrupt
    TMR0IF = 0;		    // Clear TIMER0 interrupt flag
  }
}

void main(void) 
{
    int ldr_left;
    int ldr_right;
    int ldr_diff;//gia tri khac biet
    
    TRISC2=0;
    
    ADC_Init();
    timer0();
    LCD_Init();
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String("SG90");
    __delay_ms(1000);
    LCD_Clear();
    
    while(1)
    {
        
        ldr_left = ADC_Read(0);
        ldr_right = ADC_Read(1);
   
        LCD_Set_Cursor(1,1);
        LCD_Write_String("trai ");
        LCD_Write_Number(ldr_left);
        
        LCD_Set_Cursor(2,1);
        LCD_Write_String("phai ");
        LCD_Write_Number(ldr_right);
        
        /* Get the different */
        ldr_diff = ldr_left - ldr_right;    

        if ((ldr_diff >= -THRESHOLD_VALUE) && (ldr_diff <= THRESHOLD_VALUE)) 
        {
          top_value = MAX_VALUE;     // Stop the Servo Motor
        } 
        else 
        {
          if (ldr_diff > THRESHOLD_VALUE) 
          {
            top_value = CCW_ROTATION;  // Counterclockwise Rotation
          }
          else  if (ldr_diff < -THRESHOLD_VALUE) 
          {
            top_value = CW_ROTATION;   // Clockwise Rotation
          }

          return;
        }
    }
 }
