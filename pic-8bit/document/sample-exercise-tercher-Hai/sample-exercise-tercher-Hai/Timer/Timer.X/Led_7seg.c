// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ    16000000

#include <xc.h>
#define Input  1
#define Out    0
#define kb1 PORTAbits.RA2
#define kb2 PORTAbits.RA3
#define kb3 PORTAbits.RA4
#define kb4 PORTAbits.RA5

#define Tris_kb1 TRISAbits.TRISA2
#define Tris_kb2 TRISAbits.TRISA3
#define Tris_kb3 TRISAbits.TRISA4
#define Tris_kb4 TRISAbits.TRISA5

#define Led PORTEbits.RE2
#define Tris_Led TRISEbits.TRISE2

#define Led_7SEG       PORTD
#define Tris_Led_7SEG TRISD

#define d1 PORTCbits.RC4
#define d2 PORTCbits.RC5
#define d3 PORTCbits.RC6
#define d4 PORTCbits.RC7

#define Tris_d1 TRISCbits.TRISC4
#define Tris_d2 TRISCbits.TRISC5
#define Tris_d3 TRISCbits.TRISC6
#define Tris_d4 TRISCbits.TRISC7
unsigned char bLed;
unsigned int i;
char number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  

unsigned int num,j,delay;
 unsigned long k;
 unsigned char donvi,truc,tram,ngin,digit; 
 unsigned int count, count_s;
 
void hienthi(void)
{
   	 Led_7SEG=0xff;
    switch (digit)
    {
       case 0:
          
  		    d4=1;d1=0;d2=1;d3=1;
 	        Led_7SEG=number[ngin];
          break;
        case 1:
    	 
         d1=1;d2=0;d3=1;d4=1;
         Led_7SEG=number[tram];  
          break;
        case 2:
    	 
         d1=1;d2=1;d3=0;d4=1;
         Led_7SEG=number[truc];  
          break;
          case 3:

         d1=1;d2=1;d3=1;d4=0;
         Led_7SEG=number[donvi];  
    }
      
}
void timer2_initialize ()  
{
    T2CKPS0=1;
    T2CKPS1=0;
    PR2=100;  //0.1ms
    TOUTPS0=1;
    TOUTPS1=1;
    TOUTPS2=1;
    TOUTPS2=1; //0.1/16
    TMR2ON=1;
    TMR2IE=1; 
    PEIE=1;
    GIE=1;
}

void __interrupt() Count_up(void)   
{
if (TMR2IE && TMR2IF) 
{
  TMR2IF=0;
    count++;

	 if(count==5)  //1s
	 {
      count=0;
      hienthi();
      digit++;    
      if(digit==4)
        digit=0;      
      count_s++;
      if(count_s==250)
          count_s=0;
      {  
      num++;
      
       if(num==10000)
         num=0; 
      
      ngin=num/1000;	  
       j=num%1000;
        tram=j/100;
	   j=j%100;	
       truc=j/10;
       donvi=j%10;
      }      
	  bLed=!bLed;	 
      if(bLed)
          Led=1;
      else
          Led=0;
     }
}
}

 int main ()
{
    Tris_kb1=Input;
    Tris_kb2=Input;
    Tris_kb3=Input;
    Tris_kb4=Input ;  
    Tris_Led=Out;
    Tris_d1=Out;
    Tris_d2=Out;
    Tris_d3=Out;
    Tris_d4=Out;
    Tris_Led_7SEG=0;
  
    timer2_initialize ();  
	while(1)
	{ 
        
    }      
}

