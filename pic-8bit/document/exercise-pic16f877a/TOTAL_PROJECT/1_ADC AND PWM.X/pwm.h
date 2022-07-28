/* 
 * File:   pwm.h
 * Author: Dat Nguyen
 *
 * Created on 20 November, 2021, 10:22 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    //{
    #include<xc.h>
    #include<stdint.h>

    #define TMR2PRESCALE 4
	//#define _XTAL_FREQ 20000000
    long frequency;
    
    //int PWM_Max_Duty();
    void PWM1_Init(long freq);//nomal  frequency=5000;
    void PWM2_Init(long freq);
    
    void PWM1_Set_Duty(unsigned int duty);// 0-1024
    void PWM2_Set_Duty(unsigned int duty);
    
    void PWM1_Start();
    void PWM1_Stop();
    
    void PWM2_Start();
    void PWM2_Stop();

    //}

    
#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

