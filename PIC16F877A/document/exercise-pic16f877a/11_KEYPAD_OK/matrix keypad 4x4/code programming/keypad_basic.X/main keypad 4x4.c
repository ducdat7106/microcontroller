/*
 * File:   main keypad 4x4.c
 * Author: Nguyen Duc Dat
 *
 * Created on 25 December, 2021, 10:49 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include"i2c_lcd.h"
#include"i2c_master.h"
#include"keypad_4x4.h"

char key_string_1[16];
int i=0;

void System_Init(void);
void Keypad_Screen(char *key_string);

void main(void) 
{  
    System_Init();
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String("MOI NHAP PHIM");
 
    while(1)
    {
        Keypad_Screen(key_string_1);
        LCD_Set_Cursor(2,1);
        LCD_Write_String( key_string_1 );
    }
    return;
}

/*
 *  System Init
 */

void System_Init()
{
    ADCON1 = 0x06;
    
    LCD_Init(100000);
    
    Keypad_Init();
}

void Keypad_Screen(char *key_string)
{
    char key = 'n';
    
    while(key == 'n') 
    {
        key = Keypad_Find_2();
        key_string[i] = key;
    }
      
    i++;
    if(i>15)
        i=0;
}