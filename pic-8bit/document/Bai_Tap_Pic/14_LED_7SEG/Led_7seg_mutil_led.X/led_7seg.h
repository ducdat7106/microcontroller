/*
Time: 8_2020
Author: Tuan Anh
 * 
Using Led 7seg Common Anode 
 * 
*/

#ifndef XC_LED7_H
#define	XC_LED7_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdio.h>

//#define _XTAL_FREQ 16000000

#define led_7seg PORTD
#define tris_led_7seg TRISD


#define enable_led1 PORTCbits.RC4
#define enable_led2 PORTCbits.RC5
#define enable_led3 PORTCbits.RC6
#define enable_led4 PORTCbits.RC7

#define enable_led PORTC

#define tris_enable_led1 TRISCbits.TRISC4
#define tris_enable_led2 TRISCbits.TRISC5
#define tris_enable_led3 TRISCbits.TRISC6
#define tris_enable_led4 TRISCbits.TRISC7


void Led_7seg_Init();
void Led_7seg_Display(double num);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_LED7_H */

