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
    
    
#define X_1    RB0
#define X_2    RB1
#define X_3    RB2
#define X_4    RB3
#define Y_1    RB4
#define Y_2    RB5
#define Y_3    RB6
#define Y_4    RB7
    
#define Keypad_PORT             PORTB
#define Keypad_PORT_Direction   TRISB  

void Keypad_Init(void);
char Keypad_Switch_Press_Scan(void);


#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_4X4_H */

