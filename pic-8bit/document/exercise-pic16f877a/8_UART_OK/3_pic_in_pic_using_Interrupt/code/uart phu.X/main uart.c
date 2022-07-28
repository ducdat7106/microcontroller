/*
 * File:   main uart.c
 * Author: Nguyen Duc Dat
 *
 * Created on 14 December, 2021, 11:01 AM
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
#include"uart send and get.h"

//#define _XTAL_FREQ 20000000

#define tran RA2
#define tris_tran TRISA2

#define recei PORTBbits.RB0
#define tris_recei TRISBbits.TRISB0

#define button RD7
#define tris_button TRISD7


char w_data[] = {0x44, 0x44,0x43, 0x41};

void main(void) 
{
    unsigned int i=0;
    
    ADCON1 = 0x07;
    
    tris_tran = 0;
    tran = 0;
    
    tris_recei = 0;
    recei = 0;
    
    tris_button = 1;
    
    UART_TX_AND_RX_Init(19200);
    
    while(1)
    {
        UART_Write_String(w_data);
        UART_Write_Char('\r');
        __delay_ms(500);
    }
    return;
}
