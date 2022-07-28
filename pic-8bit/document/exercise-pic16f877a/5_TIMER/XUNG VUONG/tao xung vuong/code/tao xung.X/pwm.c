#include"pwm.h"

int PWM1_Max_Duty()
{
  return(_XTAL_FREQ/(frequency1*TMR2PRESCALE));
}

int PWM2_Max_Duty()
{
  return(_XTAL_FREQ/(frequency2*TMR2PRESCALE));
}




//PR2= 0-255
void PWM1_Init(long freq)
{
  PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALE)) - 1;
  frequency1 = freq;
}

void PWM2_Init(long freq)
{
  PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALE)) - 1; //Setting the PR2 formulae using Datasheet 
  											    // Makes the PWM work in 5KHZ
  frequency2 = freq;
}

#if so == 1023
/*0-1023*/
void PWM1_Set_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM1_Max_Duty();//// On reducing //duty = (((float)duty/1023)*(1/PWM_freq)) / ((1/_XTAL_FREQ) * TMR2PRESCALE);
    CCP1CONbits.CCP1X = duty & 0x02; //Store the 1st bit
    CCP1CONbits.CCP1Y = duty & 0x01;//Store the 0th bit
    CCPR1L = duty>>0x02;// Store the remining 8 bit
  }
}
/*0-1023*/
void PWM2_Set_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM2_Max_Duty();
    CCP2CONbits.CCP2X = duty & 0x02;
    CCP2CONbits.CCP2Y = duty & 0x01;
    CCPR2L = duty>>0x02;
  }
}
#endif




#if phanTram == 100
/*0%-100%*/
void PWM1_Set_duty(unsigned int duty)
{
    duty = ((float)duty/100) * 1023; //percentage;
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP1CONbits.CCP1X = duty & 0x02;
    CCP1CONbits.CCP1Y = duty & 0x01;
    CCPR1L = duty>>0x02;
  }

  }
/*0%-100%*/
void PWM2_Set_duty(unsigned int duty)
{
    duty = ((float)duty/100) * 1023; //percentage;
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP2CONbits.CCP2X = duty & 0x02;
    CCP2CONbits.CCP2Y = duty & 0x01;
    CCPR2L = duty>>0x02;
  }
}
#endif

void PWM1_Start()
{
  CCP1M3 = 1;//Configure the CCP1 module 
  CCP1M2 = 1;
  
  ////Configure the Timer module////
  #if TMR2PRESCALAR == 1
    T2CONbits.T2CKPS0 = 0;
    T2CONbits.T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 1;
  #endif
  
  TMR2ON = 1;
  TRISC2 = 0; // make port pin on C as output
} 

void PWM1_Stop()
{
  CCP1CONbits.CCP1M3 = 0;
  CCP1CONbits.CCP1M2 = 0;
}

void PWM2_Start()
{
  CCP2CONbits.CCP2M3 = 1;
  CCP2CONbits.CCP2M2 = 1;
  
	#if TMR2PRESCALAR == 1 //uncomment these two
	    T2CKPS0 = 0;
	    T2CKPS1 = 0;
	#elif TMR2PRESCALAR == 4
	    T2CONbits.T2CKPS0 = 1;
	    T2CONbits.T2CKPS1 = 0;
	#elif TMR2PRESCALAR == 16 // uncomment these two
	    T2CKPS0 = 1;
	    T2CKPS1 = 1;
  	#endif
	    T2CONbits.TMR2ON = 1;
	    TRISC1 = 0;
}

void PWM2_Stop()
{
  CCP2CONbits.CCP2M3 = 0;
  CCP2CONbits.CCP2M2 = 0;
}

