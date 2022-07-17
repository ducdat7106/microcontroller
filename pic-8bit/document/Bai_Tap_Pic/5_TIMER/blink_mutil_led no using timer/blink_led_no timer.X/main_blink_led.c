/*
 * File:   main_blink_led.c
 * Author: DAT PC
 *
 * Created on 26 January, 2022, 3:43 PM
 */
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define LED1 PORTAbits.RA3
#define LED2 PORTAbits.RA4
#define LED3 PORTAbits.RA5

#define TRIS_LED1 TRISAbits.TRISA3
#define TRIS_LED2 TRISAbits.TRISA4
#define TRIS_LED3 TRISAbits.TRISA5

long t1=0, t2=0, t3=0;

void blinkLed();

void main(void) {
    ADCON1 = 0x06;
    
    TRIS_LED1 = TRIS_LED2 = TRIS_LED3 = 0;//OUTPUT PIN
    LED1=1;LED2=1;LED3=1;//TURN OFF
    
    while(1){
        t1++; t2++; t3++;
        __delay_us(950);
        blinkLed();
    }
    return;
}

void blinkLed(){
    if(t1>=100){
        t1=0;
        LED1^=1;
    }
//    if(t2>=100){
//        t2=0;
//        LED2^=1;
//    }
//    if(t3>=350){
//        t3=0;
//        LED3^=1;
//    }
}