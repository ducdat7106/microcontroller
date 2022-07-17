#pragma config FNOSC = PRI          // Oscillator Source Selection (Primary Oscillator XT, HS, EC)
#pragma config POSCMOD = HS         // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config JTAGEN = OFF         // JTAG Enable bit (JTAG is disabled)
#pragma config WINDIS = OFF         // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is disabled)

#include "xc.h"
#define FCY 8000000UL       //Instruction cycle frequency, Hz - required for __delayXXX() to work
#include "libpic30.h"       //__delayXXX() functions macros defined here

int main(void) {
    TRISDbits.TRISD6 = 1;       // Set PORTD - bit RD6 as Input
    TRISDbits.TRISD7 = 1;       // Set PORTD - bit RD7 as Input
    TRISA = 0;                  // Set PORTA as Output - LED enable 
    uint8_t LED_status = 0;
#ifdef __PIC24FJ1024GB610__
    ANSDbits.ANSD6 = 0;         // Disable Analog of bit RD6 PORTA
    ANSDbits.ANSD7 = 0;         // Disable Analog of bit RD7 PORTA
    ANSA = 0;                   // Disable Analog of PortA 
#endif
    while(1){
        if(!PORTDbits.RD6){             // Check when Button is pressed 
            while(!PORTDbits.RD6);      // Wait until Button is released 
            LED_status++;               // LED_status = LED_status + 1 
            LATA = LED_status;          // Turn on LED
            __delay_ms(100);            // Create anti-jamming delay
        }
        if(!PORTDbits.RD7){
            while(!PORTDbits.RD7);
            LED_status--;
            LATA = LED_status;
            __delay_ms(100);
        }
    }
    return 0;
}
