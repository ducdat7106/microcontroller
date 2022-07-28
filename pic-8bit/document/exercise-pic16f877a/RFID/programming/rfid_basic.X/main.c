/*
 * File:   main.c
 * Author: NGUYEN DUC DAT
 *
 * Created on 28 December, 2021, 10:00 AM
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
#include"i2c_master.h"
#include"uart send and get.h"
#include"i2c_lcd.h"

void System_Configure(void);

void main(void) 
{
    int i;
    unsigned char id[12];
    
    System_Configure();
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String("SHOW UR CARD");
    
    UART_Write_String("START \r\n");
    
    LCD_Set_Cursor(2,1);
    for(i=0; i<12; i++)
    {
        id[i] = UART_Read_Char();
        UART_Write_Char(id[i]);
        
        LCD_Write_Char(id[i]);
    }
    UART_Write_String("\r\nFINISH");
    while(1)
    {
        
    }
    return;
}

void System_Configure()
{
    LCD_Init(100000);
    UART_TX_AND_RX_Init(9600);
}