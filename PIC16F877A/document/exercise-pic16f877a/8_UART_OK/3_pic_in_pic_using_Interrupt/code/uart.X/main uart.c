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
#include<stdint.h>

#include"uart send and get.h"

//#define _XTAL_FREQ 20000000

#define tran RA2
#define tris_tran TRISA2

#define recei PORTBbits.RB0
#define tris_recei TRISBbits.TRISB0

#define button RD7
#define tris_button TRISD7


char w_data[] = {0x66, 0x04,0x03, 0x11, 0x67};
char r_data[10] ;
char data;


uint16_t UART_Buffer = 0;
char UART_Array_Buffer[10];
int m=0;

void __interrupt() isr()
{
    if (RCIE && RCIF)
    {
       
        UART_Buffer = RCREG; // Read The Received Data Buffer
        UART_Array_Buffer[m++] = UART_Buffer;
        if(m>6)//so luong phan tu + ky tu ket thuc chuoi
            m=0;

        RCIF = 0; // Clear The Flag
    }
}

void main(void) 
{
    unsigned int i=0;
    
    ADCON1 = 0x07;
    
    tris_tran = 0;
    tran = 0;
    
    tris_recei = 0;
    recei = 0;
    
    tris_button = 1;
    
     RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
  
    UART_TX_AND_RX_Init(19200);
    
    UART_Write_String(w_data);
    
    while(1)
    {
        //UART_Read_String(r_data, 7);//nhan 5 byte du lieu
        //data = UART_Read_Char();
        //UART_Write_Char(data);//gui nguoc lai 5 byte vua nhan
        if(m>=6)
        {
        UART_Write_String(UART_Array_Buffer);
        m=0;
        }
    }
    return;
}
