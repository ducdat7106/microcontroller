/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 27 November, 2021, 7:16 AM
 */


#include <xc.h>
#include"external_eeprom.h"

//#define _XTAL_FREQ 16000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void write_byte_style_1();
void write_byte_style_2();
void write_page();

int main()
{
    TRISB  = 0;             // To make it output port
    PORTB = 0;              // To make it output port
    CMCON = 0x07;           // To turn off comparators
    ADCON1 = 0x06;          // To turn off analog to digital converters
    
    EEPROM_Init(100);
    
//    write_page();
    write_byte_style_2();
    while(1)
    {
//        write_byte();
    }  
    return 0;
}

//ghi byte roi rac
void write_byte_style_1()
{
    unsigned int a;
    unsigned char i;
    
    for(i=0,a=1;i<8;i++)
        {
           EEPROM_Write(i, (unsigned char)a);
           __delay_ms(100);
           a = a<<1;//a=0x01 << i
        }
        
        __delay_ms(1000);
        
        for(i=0;i<8;i++)
        {
           PORTB = EEPROM_Read(i);
           __delay_ms(1000);
        }
}

void write_byte_style_2()
{
    unsigned char Address = 0x0020; // Some Random Address
    unsigned char Data = 0x04;     // Some Random Data To Write

    EEPROM_Write(Address++, Data++); // Write 0x04 @ 0x0020
    EEPROM_Write(Address++, Data++); // Write 0x05 @ 0x0021
    EEPROM_Write(Address, Data);     // Write 0x06 @ 0x0022
    __delay_ms(10); // Wait tWR=10ms For Write To Complete

    Address = 0x0020; // Point To First Byte Location
    PORTB = EEPROM_Read(Address++); // Should Read 0x04
    __delay_ms(1000);
    PORTB = EEPROM_Read(Address++); // Should Read 0x05
    __delay_ms(1000);
    PORTB = EEPROM_Read(Address);   // Should Read 0x06
    __delay_ms(1000);
}


//ham nay khong nam trong while(1)
//va chi duoc goi 1 lan duy nhat--->nam tren while(1)
void write_page()
{
    unsigned char Address = 0x0020; // Some Random Address
    // Some Random Data BufferTo Write
    unsigned char Buffer[5] = {0x08, 0x10, 0x20, 0x40, 0x80};
    unsigned char ReadBuffer[5];

    //---[ Write Page ]---
    EEPROM_Write_Page(Address, Buffer, 5);
    __delay_ms(10); // Wait tWR=10ms For Write To Complete

    //---[ Read Page ]---
    EEPROM_Read_Page(Address, ReadBuffer, 5);
    for(int i=0; i<5; i++)
    {
      PORTB = ReadBuffer[i];
      __delay_ms(1000);
    }
}