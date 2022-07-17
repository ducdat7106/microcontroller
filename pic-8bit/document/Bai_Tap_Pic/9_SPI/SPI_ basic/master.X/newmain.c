 /*
 * File            : newmain.c
 * Author          : Ligo George
 * Company         : electroSome
 * Project         : SPI Master Example
 * Microcontroller : PIC 16F877A
 * Created on April 15, 2017, 5:59 PM
 */

// PIC16F877A Configuration Bit Settings
// 'C' source line config statements

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = XT   // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF   // Low-Voltage In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit 
#pragma config WRT = OFF   // Flash Program Memory Write Enable bits 
#pragma config CP = OFF    // Flash Program Memory Code Protection bit

#include <xc.h>
#include <pic16f877a.h>
#include "spi.h"

#define _XTAL_FREQ 8000000

void main()
{
   nRBPU = 0;                    //Enable PORTB internal pull up resistor
   TRISB = 0xFF;                 //PORTB as input
   TRISD = 0x00;                 //PORTD as output
   PORTD = 0x00;                 //All LEDs OFF
   TRISC7 = 0;
   RC7 = 1;
   
   spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
   
   while(1)
   {
       RC7 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(PORTB);
       PORTD = spiRead();
       
       __delay_ms(1);
       RC7 = 1;       //Slave Deselect 
       
       __delay_ms(100);
   }
}