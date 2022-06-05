#include "main.h"

int main()
{
    initADC();
    initPin();
    
    while(1)
    {
        blinkLed();
    }
    return 0;
}

void initADC()
{
    #ifdef __PIC24FJ1024GB610__
        ANSA = 0;                   // Disable Analog of PortA 
    #endif
}

void  mydelay_ms(unsigned long ms)
{
    unsigned long i;
    for(i=0; i<ms; i++)
    {
        __delay_ms(1);
    }
}

