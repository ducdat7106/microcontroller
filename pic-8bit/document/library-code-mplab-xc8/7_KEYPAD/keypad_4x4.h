/* 
 * File:   keypad 4x4.h
 * Author: Nguyen Duc Dat
 *
 * Created on 25 December, 2021, 10:48 AM
 */

#ifndef KEYPAD_4X4_H
#define	KEYPAD_4X4_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>    
    
#define R1    RB0 //row is output
#define R2    RB1
#define R3    RB2
#define R4    RB3
    
#define C1    RB4//column is input
#define C2    RB5
#define C3    RB6
#define C4    RB7
    
    
    
#define Keypad_PORT             PORTB
#define Keypad_PORT_Direction   TRISB  

void Keypad_Init();
char Keypad_Find_1();

char Keypad_Find_2();


#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_4X4_H */

