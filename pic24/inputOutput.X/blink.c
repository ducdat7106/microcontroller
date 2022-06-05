#include "blink.h"

// void  mydelay_ms();
extern void  mydelay_ms(unsigned long ms);

void initPin()
{
    TRISA = 0;                    // Set PortA as output - LED enabled  
    LATA = 0;
}

void blinkLedBasic()
{
    static uint8_t LED_status = 0xFF; 
    LATA = LED_status;              // Turn on LED
    LED_status = ~LED_status;       // Inverting all bits in LED_status 
    mydelay_ms(1000);               

}