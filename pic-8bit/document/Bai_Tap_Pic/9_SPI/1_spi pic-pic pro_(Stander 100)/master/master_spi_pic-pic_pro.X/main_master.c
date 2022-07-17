/*
 * File:   main_master.c
 * Author: Nguyen Duc Dat
 
 * Created on 12 December, 2021, 7:03 AM
 */

#include <xc.h>
#include"config.h"
#include"spi.h"

//#define _XTAL_FREQ 8000000
#define ENABLE_SLAVE PORTCbits.RC7
#define TRIS_ENABLE_SLAVE TRISCbits.TRISC7

#define LED PORTD
#define TRIS_LED TRISD

#define buttonUp PORTBbits.RB0
#define buttonDown PORTBbits.RB1
#define buttonSent PORTBbits.RB2
#define tris_buttonUp TRISBbits.TRISB0
#define tris_buttonDown TRISBbits.TRISB1
#define tris_buttonSent TRISBbits.TRISB2


void main(void) 
{
    ADCON1 = 0x07;
    nRBPU = 0;    //Enable PORTB internal pull up resistor
    
    TRIS_LED = 0x00;    //TRIS_LED as output
    LED = 0;    //All LEDs OFF
    
    TRIS_ENABLE_SLAVE = 0;//TRIS_ENABLE_SLAVE as output
    
    char w_data = 0;
    char r_data = 0;
    
    SPI_Init_Advanced(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while(1)
    {
        
        if(!buttonUp)
        {
            w_data++;
            __delay_ms(250);
        }
        if(!buttonDown)
        {
            w_data--;
            __delay_ms(250);
        }
        
        ENABLE_SLAVE = 0;//Slave Select
        __delay_ms(1);
        
        //if(!buttonSent)
        {
            SPI_Write(w_data);
            __delay_ms(250);
        }
        
        r_data = SPI_Read();
        LED = r_data;
        
        ENABLE_SLAVE = 1;//Slave Deselect
        
        __delay_ms(100);
    }
    return;
}
////////////////////////////////// if using interrupt/////////////////////////////
/*
* File : newmain.c
* Author : Ligo George
* Company : electroSome
* Project : SPI Slave Example
* Microcontroller : PIC 16F877A
* Created on April 15, 2017, 5:59 PM
*/

// PIC16F877A Configuration Bit Settings
// 'C' source line config statements

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
/*
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


void interrupt SPI_Slave_Read()
{
  if(SSPIF == 1)
  {
    PORTD = spiRead();
    spiWrite(PORTB);
    SSPIF = 0;
  }
}

void main()
{
  nRBPU = 0;    //Enable PORTB internal pull up resistor
  TRISB = 0xFF; //PORTB as input
  TRISD = 0x00; //PORTD as output
  PORTD = 0x00; //All LEDs OFF

  GIE = 1;
  PEIE = 1;
  SSPIF = 0;
  SSPIE = 1;
  ADCON1 = 0x07;
  TRISA5 = 1;

  spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

  while(1)
  {
    //Do something here
    __delay_ms(5);
  }
}
*/