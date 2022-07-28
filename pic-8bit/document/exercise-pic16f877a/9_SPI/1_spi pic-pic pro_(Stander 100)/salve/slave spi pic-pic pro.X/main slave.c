/*
 * File:   main slave.c
 * Author: Nguyen Duc Dat
 *
 * Created on 12 December, 2021, 7:57 AM
 */

#include <xc.h>
#include"config_slave.h"
#include"spi.h"

//#define _XTAL_FREQ 8000000
#define ENABLE_SLAVE PORTAbits.RA5
#define TRIS_ENABLE_SLAVE TRISAbits.TRISA5

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
    ADCON1=0x07;
    nRBPU = 0;    //Enable PORTB internal pull up resistor
    
    TRIS_LED = 0x00;//TRIS_LED as output
    LED = 0x00;//turn off all leds
    
    TRIS_ENABLE_SLAVE = 1;//TRIS_ENABLE_SLAVE as input
    
    char w_data = 0;
    char r_data = 0;
    
    SPI_Init(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
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
        
        //if(!buttonSent)
        {
            //SPI_Write(w_data);
        }
        
        
        if(SPI_DataReady())
        {
            r_data = SPI_Read();
            SPI_Write(w_data);
        }
        LED = r_data;
    }
    return;
}
