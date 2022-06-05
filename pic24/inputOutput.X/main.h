/* 
 * File:   main.h
 * Author: Nguyet
 *
 * Created on 25 May, 2022, 3:21 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #pragma config FNOSC = PRI          // Oscillator Source Selection (Primary Oscillator XT, HS, EC)
    #pragma config POSCMOD = HS         // Primary Oscillator Select (HS Oscillator mode selected)
    #pragma config JTAGEN = OFF         // JTAG Enable bit (JTAG is disabled)
    #pragma config WINDIS = OFF         // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
    #pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is disabled)

    #include "xc.h"
    #define FCY 8000000UL       //Instruction cycle frequency, Hz - required for __delayXXX() to work
    #include "libpic30.h"       //__delayXXX() functions macros defined here

    #include "blink.h"

    void  mydelay_ms(unsigned long ms);
    
    void initADC();

    

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

