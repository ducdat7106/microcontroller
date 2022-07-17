/*
 * File:   main_hs_cr_04.c
 * Author: DAT PC
 *
 * Created on 27 January, 2022, 4:38 AM
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "LCD.h"
#include "HC_SR_04.h"

#define _XTAL_FREQ 20000000


float time_taken;
float distance;
char t1,t2,t3,t4,t5;
char d1,d2,d3;


void Config_Init();



int main(void) {
    Config_Init();
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String("Ultrasonic sensor");
    LCD_Set_Cursor(2,1);
    LCD_Write_String("with PIC16F877A");

    __delay_ms(2000);
    LCD_Clear();
        
    while(1){
        time_taken = HC_SR_04_Time_Taken();
        
        distance = HC_SR_04_Distance( time_taken );
        
        time_taken = time_taken * 0.8;
        
        t1 = (char)(time_taken/1000)%10;
        t2 = (char)(time_taken/1000)%10;
        t3 = (char)(time_taken/100)%10;
        t4 = (char)(time_taken/10)%10;
        t5 = (char)(time_taken/1)%10;
        d1 = (char)(distance/100)%10;
        d2 = (char)(distance/10)%10;
        d3 = (char)(distance/1)%10;
        
        LCD_Set_Cursor(1,1);
        LCD_Write_String("Time_taken:");
        LCD_Write_Char(t1+'0');
        LCD_Write_Char(t2+'0');
        LCD_Write_Char(t3+'0');
        LCD_Write_Char(t4+'0');
        LCD_Write_Char(t5+'0');

        LCD_Set_Cursor(2,1);
        LCD_Write_String("distance:");
        LCD_Write_Char(d1+'0');
        LCD_Write_Char(d2+'0');
        LCD_Write_Char(d3+'0');      
    }
    return 0;
}


void Config_Init(){
    ADCON1 = 0x06;

    LCD_Init();
    
    HC_SR_04_Init();
}