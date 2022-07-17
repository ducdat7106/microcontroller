#pragma config FNOSC = PRI          // Oscillator Source Selection (Primary Oscillator XT, HS, EC)
#pragma config POSCMOD = HS         // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config JTAGEN = OFF         // JTAG Enable bit (JTAG is disabled)
#pragma config WINDIS = OFF         // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is disabled)

#include "xc.h"
#define FCY 8000000UL       //Instruction cycle frequency, Hz - required for __delayXXX() to work
#include "libpic30.h"       //__delayXXX() functions macros defined here

int main(void) {
      TRISA = 0;                    // Set PortA as output - LED enabled 
      uint8_t LED_status = 0xFF;    
#ifdef __PIC24FJ1024GB610__
    ANSA = 0;                   // Disable Analog of PortA 
#endif
    while(1){                           // Endless Loop
        LATA = LED_status;              // Turn on LED
        LED_status = ~LED_status;       // Inverting all bits in LED_status 
        __delay_ms(500);                // Delay 0.5s
    }
    return 0;
}
