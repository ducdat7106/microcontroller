/* 
 * File:   step_motor.h
 * Author: DAT PC
 *
 * Created on 26 January, 2022, 4:27 PM
 */

#ifndef STEP_MOTOR_H
#define	STEP_MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
#define IN1 PORTDbits.RD0
#define IN2 PORTDbits.RD1
#define IN3 PORTDbits.RD2
#define IN4 PORTDbits.RD3

#define TRIS_IN1 TRISDbits.TRISD0
#define TRIS_IN2 TRISDbits.TRISD1
#define TRIS_IN3 TRISDbits.TRISD2
#define TRIS_IN4 TRISDbits.TRISD3
    
void Step_Motor_Init();
void Wave_Drive_Mode(char, unsigned int);
void Full_Drive_Mode(char, unsigned int);
void Half_Drive_Mode(char, unsigned int);



#ifdef	__cplusplus
}
#endif

#endif	/* STEP_MOTOR_H */

