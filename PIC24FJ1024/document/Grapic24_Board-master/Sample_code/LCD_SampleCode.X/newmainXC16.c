#pragma config FNOSC = PRI          // Oscillator Source Selection (Primary Oscillator XT, HS, EC)
#pragma config POSCMOD = HS         // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config JTAGEN = OFF         // JTAG Enable bit (JTAG is disabled)
#pragma config WINDIS = OFF         // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is disabled)

#include "xc.h"
#define FCY 8000000UL       //Instruction cycle frequency, Hz - required for __delayXXX() to work
#include "libpic30.h"       //__delayXXX() functions macros defined here
#include "lcd.h"            // Include lcd library

int main(void) {
    LCD_Initialize();       // Initialize LCD
    while(1){
        printf("   Welcome to   \r\n");     // print sting in LCD
        printf("   Grapetech!   ");         
        __delay_ms(500);                    // Create anti-jamming delay
        LCD_ClearScreen();                  // Clear LCD screen
    }
    return 0;
}
