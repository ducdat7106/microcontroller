#include<xc.h>
#include<stdint.h>

#define TMR2PRESCALE 4

#define TMR2PRESCALE TMR2PRESCALAR

#define _XTAL_FREQ 16000000

#define phanTram 100
//#define so  1024
	
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



