#pragma config FNOSC = PRI          // Oscillator Source Selection (Primary Oscillator XT, HS, EC)
#pragma config POSCMOD = HS         // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config JTAGEN = OFF         // JTAG Enable bit (JTAG is disabled)
#pragma config WINDIS = OFF         // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is disabled)

#include "xc.h"
#define FCY 8000000UL       //Instruction cycle frequency, Hz - required for __delayXXX() to work
#include "libpic30.h"       //__delayXXX() functions macros defined here

volatile uint8_t Timer1_flag = 0;
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF =0;       // reset the interrupt flag
    Timer1_flag = 1;         
}

void Timer1_init(int value){
    T1CONbits.TON = 0;          // Start/Stop bit - Stop Timer
    T1CONbits.TCKPS = 0x03;     // Timer prescaler 1:256
    T1CONbits.TCS = 0x00;       // Using FOSC/2 
    PR1 = value;                // Load the Timer period value into PR1 register
    IPC0bits.T1IP =1;           // Set interrupt priority
    IFS0bits.T1IF =0;           // Reset interrupt flag
    IEC0bits.T1IE =1;           // Turn on the timer1 interrupt    
}

void Timer1_Start(){
    T1CONbits.TON =1;           // Start Timer
}
int main(void) {                // Main function 
    uint16_t sec = 0;           
    TRISA = 0;                  // Set PortA as output - LED enable
#ifdef __PIC24FJ1024GB610__
    ANSA = 0;                   // Disable Analog of PortA 
#endif
    Timer1_init(15625);         // Initialize Timer1, the interrupt event occurred in 1s = (1*2*256/FCY)*15625
    Timer1_Start();             // Start Timer1
    while(1){                   // Endless Loop
        if(Timer1_flag)         // When interrupt event occurred 
        {
            sec++; 
            LATA = sec;         // Turn on LED 
            Timer1_flag = 0;    // Reset Interrupt flag 
        }
    }
    return 0;
}
