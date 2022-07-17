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
#include <xc.h>
#include "lcd_hd44780_pic16.h" 
#include "ADC0808.h"

#define Input  1
#define Out    0

unsigned int i;
float Dong,Dienap;
unsigned int count, count1,count_s;
unsigned char do_dienap;
unsigned char adc_ok;

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
void interrupt isr()     //1ms
{
  if (TMR2IE && TMR2IF) 
   {
  TMR2IF=0;
    count++;
       if(count==20)  //20ms
       {
         count=0;
         count1++;
        if(do_dienap)
        {
          Dienap=(float)(ReadADC(AN0));     
          Dienap=Dienap*1.962;
          adc_ok=1;       
        }
         else
         {
         Dong = (float)(ReadADC(AN1));		// Read ADC value from Channel 1 
         Dong=Dong/2.55;
         } 
         do_dienap=~do_dienap;    
       }
  }
}

int main ()
{
    unsigned char Digit[3] = { 0,0,0 };	// To make digits to display on LCD
    unsigned int ADC_Value = 0;	
    
    
    ADCON1 = 0x06;
   LCDInit(LS_NONE);
   InitADC();
   timer2_initialize ();
  //Clear the display
  LCDClear();
  
   LCDWriteString("Do U/I ...");	// Show Welcome Message
    
    __delay_ms(100);
    LCDClear();
	while(1)
	{   
       if(adc_ok&&count1==25)
       {        
         count1=0;
         ADC_Value=(unsigned int)Dong;
		Digit[2] = (ADC_Value/100);		  			// Find out first digit
		Digit[1] =  (ADC_Value%100)/10;
		Digit[0] = (ADC_Value%100)%10;

		//ClearLCDScreen();											// Clear LCD
      LCDGotoXY(1,0);
	LCDWriteString("Gia tri I= ");							// Display string
	LCDData(Digit[2]+0x30);
	LCDData('.');						// Display first digit
	LCDData(Digit[1]+0x30);								// Display second digit
	LCDData(Digit[0]+0x30);								// Display third digit
		
		//lcd_putch(Didit);
        
		ADC_Value=(unsigned int)Dienap;
		Digit[2] = (ADC_Value/100);		  			// Find out first digit
		Digit[1] =  (ADC_Value%100)/10;
		Digit[0] = (ADC_Value%100)%10;

     LCDGotoXY(1,1);
	LCDWriteString("Gia tri U= ");							// Display string
	LCDData(Digit[2]+0x30);
	LCDData('.');						// Display first digit
	LCDData(Digit[1]+0x30);								// Display second digit
	LCDData(Digit[0]+0x30);	
     } 
      }
   }

