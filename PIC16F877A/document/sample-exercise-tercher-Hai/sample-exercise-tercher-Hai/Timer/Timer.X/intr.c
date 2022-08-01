#include	<htc.h>
unsigned char Timer_100ms;
bit Enb1=0,Enb2=0;

const unsigned int pwmtable[100]=
{
0,
79,
157,
236,
314,
392,
471,
549,
627,
705,
782,
860,
937,
1014,
1091,
1167,
1243,
1319,
1395,
1470,
1545,
1620,
1694,
1767,
1841,
1913,
1986,
2058,
2129,
2200,
2270,
2340,
2409,
2477,
2545,
2612,
2679,
2745,
2810,
2875,
2939,
3002,
3065,
3126,
3187,
3247,
3307,
3365,
3423,
3480,
3536,
3591,
3645,
3698,
3751,
3802,
3853,
3902,
3951,
3998,
4045,
4091,
4135,
4179,
4222,
4263,
4304,
4343,
4382,
4419,
4455,
4490,
4524,
4557,
4589,
4619,
4649,
4677,
4704,
4730,
4755,
4779,
4801,
4823,
4843,
4862,
4880,
4896,
4911,
4926,
4938,
4950,
4961,
4970,
4978,
4985,
4990,
4994,
4998,
4999,
};

bank3 unsigned char pwm[50];
unsigned char pwm1[50];
 int Count_sin=0;

unsigned int ADC_Value;
bit Blink;
unsigned int ccp;
static void interrupt isr(void)			// Here be interrupt function - the name is unimportant.
{
 /*
      Blink=!Blink;
        if(Blink)
           RC2=0;
          else
         RC2=1;
 */
  if(TMR2IF)
  {    
    TMR2IF=0;
      
    if (Count_sin<100)
   {      
       ECCPASE=0;
       
       if(Count_sin<50)
        ccp=(pwm[Count_sin]*4);
       else
        ccp=(pwm1[Count_sin-50]*4);

       if(Count_sin==99)
          GODONE=1;
   }
   else
   {
     if(Count_sin<200)  //   100<Count_sin<200
      {
          if(Count_sin<150)
           ccp=(pwm1[149-Count_sin]*4);
       else
        ccp=(pwm[199-Count_sin]*4);
	  }
     else
      {
        if(Count_sin<300)  //200<Count_sin<300
        {
            ECCPASE=0;
             if(Count_sin<250)
               ccp=(1000-pwm[Count_sin-200]*4);
              else
               ccp=(1000-pwm1[Count_sin-250]*4);
        }
        else  //>300  
        {
          if(Count_sin<350)
               ccp=(1000-pwm1[349-Count_sin]*4);
              else
               ccp=(1000-pwm[399-Count_sin]*4);
        }
      }
   }
        
    if(ccp&0x0002)
     DC1B1=1;
    else
      DC1B1=0;
    if(ccp&0x0001)
     DC1B0=1;
    else
     DC1B0=0;
     
      CCPR1L=ccp>>2;
   
     if(Count_sin==199)
           {
             ECCPASE=1;    
             RC0=0;
             RC0=0;
             RC0=0;
             RC0=0;
             RC0=0;
      		 RC1=1;
           }   
     if(Count_sin==399) //20ms
           {
            Count_sin=0;
             ECCPASE=1;
             RC1=0;
             RC1=0;
             RC1=0;
             RC1=0;
             RC0=1;
             Timer_100ms++;
             Enb1=1;
           } 
     Count_sin++;
     }

  if(ADIF)
  {
   ADIF=0;
   ADC_Value=256*(unsigned int)(ADRESH)+ADRESL;   
  }

  if(INTF)  //INT flag bit
  {
  /* INTF=0;
   RC0=0;
   RC1=0;
   ECCPASE=1;
   di();*/
  }
}
