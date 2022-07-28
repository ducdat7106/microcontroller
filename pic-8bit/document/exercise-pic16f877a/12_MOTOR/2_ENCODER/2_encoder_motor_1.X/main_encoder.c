/*
 * File:   main_encoder.c
 * Author: Dat Nguyen
 *
 * Created on 28 November, 2021, 4:36 AM
 */



/*
 * File:   main.c
 * Project: Motor RPM Measurement
 * Author: Khaled Magdy
 * Tasks:
 *        1- Use Hardware Counter Module
 *        2- Use Timer/Capture
 *        3- #include<stdio.h> and use sprintf() Function
 
    ------------------2013-----------------------
 */
//=========================================================

#include <xc.h>
#include"lcd.h"
#include<stdint.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000

//*
//--------------------------
//-----[ Globals ]-----
uint32_t RPM=0, RPS=0, Encoder1_Ticks=0;
uint8_t TMR1_C=0;
char RPM_S[10]="0000      ";
char RPS_S[10]="0000      ";
char* line1 = "RPS = ";
char* line2 = "RPM = ";
//========================================


//-----[ Prototypes For All Functions ]-----
void Update_LCD();
void Display_Init();
void Timer1_Init();
void AttachInterrupts();

//===============================================



int main(void) 
{
    ADCON1=0x06;
    
    LCD_Init();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("hello");
    __delay_ms(1000);
    LCD_Clear();
    
    Display_Init();
    
    Timer1_Init();
    AttachInterrupts();
    
    while(1)
    {
        Update_LCD();
        __delay_ms(50);
    }
    return 0;
}

void __interrupt() ISR()
{
    if(INTE && INTF)
    {
        Encoder1_Ticks++;
        INTF=0;
    }
    
    if(TMR1IE && TMR1IF)
    {
        TMR1_C++;
        if(TMR1_C==2)
        {
            TMR1_C=0;
            RPS = Encoder1_Ticks;
            RPM = RPS * 60;
            Encoder1_Ticks = 0;
        }
        TMR1 = 3036;
        TMR1IF = 0;
    }
}


void Update_LCD()
{
    if(RPM < 9999) // Upper Limit
    {
        int Temp = RPS, div=1000;
        for(int i=0; i<4; i++)
        {
            RPS_S[i] = (Temp / div)+48;
            Temp = Temp%div;
            div/=10;
        }
        LCD_Set_Cursor(1, 7);
        LCD_Write_String(RPS_S);
        
        int Temp1 = RPM; div=1000;
        for(int i=0; i<4; i++)
        {
            RPM_S[i] = (Temp1 / div)+48;
            Temp1 = Temp1%div;
            div/=10;
        }
        
        LCD_Set_Cursor(2, 7);
        LCD_Write_String(RPM_S);
    }
}
void Display_Init()
{
    // Print The Main Body of The UI Text
    LCD_Set_Cursor(1,1);
    LCD_Write_String(line1);
    LCD_Set_Cursor(2,1);
    LCD_Write_String(line2);
}
//--------------------------------------------


//--------------------------------------------//-----[ Interrupts Configuration Routines ]-----
void AttachInterrupts()
{
    // Set The RB0 Pin To Be an Input Pin
    //TRISB0 = 1;
    // Set The IRQ Edge
    INTEDG = 0;
    // Enable RB0 IRQ
    INTE = 1;
    //PEIE = 1;
    GIE = 1;
}
//--------------------------------------------


//-----[ Timer1 Routines ]-----
void Timer1_Init()
{
  // -- [[ Configure Timer1 To Operate In Timer Mode ]] --
  // Preload The Value Which We've Calculated To The TMR1 16-Bit Register!
  TMR1 = 3036; // For 20 Intervals Per 1 Second ! (Every 25ms)
  // Choose the local clock source (timer mode)
  TMR1CS = 0;
  // Choose the desired prescaler ratio (1:2)
  T1CKPS0 = 1;
  T1CKPS1 = 0;
  // Switch ON Timer1 Module!
  TMR1ON = 1;
  // Enable TMR1 Interrupt
  TMR1IE = 1;
  
  PEIE=1;
  GIE=1;
}
//--------------------------------------

