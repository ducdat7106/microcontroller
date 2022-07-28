/* 
 * File:   pwm.h
 * Author: Nguyen Duc Dat
 *
 * Created on 16 December, 2021, 12:59 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include<stdint.h>

//#define TMR2PRESCALE 1
#define TMR2PRESCALE 4
//#define TMR2PRESCALE 16

#define  TMR2PRESCALAR TMR2PRESCALE
//#define _XTAL_FREQ 20000000

#define phanTram 100 //ung dung vao nut bam dieu khien dong co

//#define phanTram 1024 //ung dung vao bien tro dieu khien dong co
	
long frequency1,  frequency2 ;
    
int PWM1_Max_Duty();
int PWM2_Max_Duty();

void PWM1_Init(long freq);//nomal  frequency>=5000;tao sung 5k
void PWM2_Init(long freq);

void PWM1_Set_Duty(unsigned int duty);
void PWM2_Set_Duty(unsigned int duty);

void PWM1_Start();
void PWM1_Stop();

void PWM2_Start();
void PWM2_Stop();

//////////////////////////////////////////////////


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

