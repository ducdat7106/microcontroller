#define _XTAL_FREQ 4000000
#define TMR2PRESCALE 4
long freq;

/*this function calculate the maximum duty cycle value when we had defined Fosc and Timer 2 prescaler
for this example, MaxDuty = 1000 if we choose the frequency of pulse equal 1khz*/
int PWM_Max_Duty()
{
  return(_XTAL_FREQ/(freq*TMR2PRESCALE));
}
/*this function init the frequency of pulse*/
int PWM1_Init_Fre(long fre)
{
  PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALE)) - 1;
  freq = fre;
}
int PWM2_Init_Fre(long fre)
{
  PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALE)) - 1;
  freq = fre;
}
/*duty value is as percent,its value is between 0 and 100 percent*/
int PWM1_Duty(unsigned int duty)
{
    duty = ((float)duty/100.0)*PWM_Max_Duty();
    CCP1X = duty & 2;
    CCP1Y = duty & 1;
    CCPR1L = duty>>2;
}
int PWM2_Duty(unsigned int duty)
{
    duty = ((float)duty/100.0)*PWM_Max_Duty();
    CCP2X = duty & 2;
    CCP2Y = duty & 1;
    CCPR2L = duty>>2;
}
/* this function allow PWM module run immediately*/
void PWM1_Start()
{
  CCP1CONbits.CCP1M3 = 1;
  CCP1CONbits.CCP1M2 = 1;
  #if TMR2PRESCALE == 1
    T2CONbits_t.T2CKPS0 = 0;
    T2CONbits_t.T2CKPS1 = 0;
  #elif TMR2PRESCALE == 4
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;
  #elif TMR2PRESCALE == 16
    T2CONbits_t.T2CKPS0 = 1;
    T2CONbits_t.T2CKPS1 = 1;
  #endif
  T2CONbits.TMR2ON = 1;
  TRISCbits.TRISC2 = 0;
}
void PWM2_Start()
{
  CCP2CONbits.CCP2M3 = 1;
  CCP2CONbits.CCP2M2 = 1;
  #if TMR2PRESCALE == 1
    T2CONbits_t.T2CKPS0 = 0;
    T2CONbits_t.T2CKPS1 = 0;
  #elif TMR2PRESCALE == 4
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;
  #elif TMR2PRESCALE == 16
    T2CONbits_t.T2CKPS0 = 1;
    T2CONbits_t.T2CKPS1 = 1;
  #endif
    T2CONbits.TMR2ON = 1;
    TRISCbits.TRISC1 = 0;
}
/*this function stop PWM module.*/
void PWM1_Stop()
{
  CCP1CONbits.CCP1M3 = 0;
  CCP1CONbits.CCP1M2 = 0;
}
void PWM2_Stop()
{
  CCP2CONbits.CCP2M3 = 0;
  CCP2CONbits.CCP2M2 = 0;
}
