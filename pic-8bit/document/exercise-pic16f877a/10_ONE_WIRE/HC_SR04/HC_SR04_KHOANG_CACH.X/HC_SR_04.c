#include "HC_SR_04.h"

void timer1()
{
    //T1CON=0x20; //4 pres-scalar and internal clock
    TMR1H =0; TMR1L =0; //clear the timer bits
    
    T1CONbits.T1CKPS1 = //1:4
    T1CONbits.T1CKPS0 = 0;
    
    T1CONbits.TMR1CS = 0;
    
    T1CONbits.T1SYNC = 1;
    
    TMR1IE=1;
    PEIE=1;
    GIE=1;
}

void HC_SR_04_Init(){
    Tris_Echo = 1;   //Echo pin of US sensor is set as input pin   
    
    Tris_Trigger =0; //Trigger pin of US sensor is sent as output pin
    Trigger = 0;
    
    timer1();
}

float HC_SR_04_Time_Taken(){
    float time_taken_value=0;
    
    TMR1H =0; TMR1L =0; //clear the timer bits

    Trigger = 1; 
    __delay_us(10);           
    Trigger = 0; 
    
    while (Echo==0);
        TMR1ON = 1;
    while (Echo==1);
        TMR1ON = 0;
        
    time_taken_value = (TMR1L | (TMR1H<<8)); 
    
    return time_taken_value;  
}


/*
 Time = (16-bit register value) * (1/Internal Clock) * (Pre-scale)
Internal Clock = Fosc/4

Where in our case,
Fosc = 20000000Mhz and Pre-scale = 4

Hence the value of Internal Clock will be 5000000Mhz and the value of time will be

Time = (16-bit register value) * (1/5000000) * (4)
          = (16-bit register value) * (4/5000000)
          = (16-bit register value) * 0.0000008 seconds (OR)
Time = (16-bit register value) * 0.8 micro seconds

 
 return function HC_SR_04_Time_Taken() *0.8 
 */



/*
 The speed of us wave (sound) is 34000cm/s.
  
 Distance = (Speed*Time)/2
                = (34000 * (16-bit register value) * 0.0000008) /2
Distance = (0.0272 * 16-bit register value)/2
 * 
 * 
 distance= (0.0272*time_taken)/2;
 * 
 * 
 distance from 2cm to 350cm with an accuracy of 0.5cm
 */
float HC_SR_04_Distance( float time_taken_value ){
    float distance_value=0;
    
    distance_value= ( 0.0272*time_taken_value )/2;
    
    return distance_value;
}