
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
#include <string.h>

#define Input  1
#define Out    0
#define Led PORTEbits.RE2
#define Tris_Led TRISEbits.TRISE2

unsigned int i;
float Dong,Dienap;
unsigned int count, count1,count_s;
unsigned char do_dienap;
float Dong,Dienap;
unsigned char adc_ok;


char in_buffer[6];
unsigned char in_count;
unsigned char check_sang;


extern void InitADC(void);
extern unsigned int ReadAdc(unsigned char Channel);
extern void Init_uart(void);
extern void Send_data(unsigned int Value);

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
void __interrupt()  isr()      //1ms
{
    char ch; 
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
          Dienap=(float)(ReadAdc(0));     
          Dienap=Dienap*0.489;
          adc_ok=1;       
        }
         else
         {
         Dong = (float)(ReadAdc(1));		// Read ADC value from Channel 1 
         Dong=Dong*0.0978;
         } 
         do_dienap=~do_dienap;    
       }
  }
  if (RCIE && RCIF) 
   {
       ch=RCREG;
       if(check_sang)
        in_buffer[in_count++]=ch;	 //   "Sangjhhfhfggdgdgdgdggdgdgdgdgdfhfh"

	  if(in_count==6) 
	  {
	     in_count=0; 
		 check_sang=0;
	  }
		

      if(ch=='{')
       {
        in_count=0;
        check_sang=1;
       }
      if(ch=='}')
       {
         check_sang=0; 
         if(strncmp(in_buffer,"Sang",4)==0)       
           Led=0;  
         if(strncmp(in_buffer,"Tat",3)==0)       
           Led=1;     
       }
  
	}
}

int main ()
{
    unsigned char Digit[3] = { 0,0,0 };	// To make digits to display on LCD
    unsigned int ADC_Value = 0;	
    
    Tris_Led=Out;
   InitADC();
   LCDInit(LS_NONE);
   
   timer2_initialize ();
  //Clear the display
  LCDClear();
  Init_uart();
  
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
       Send_data(ADC_Value);
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
      Send_data(ADC_Value);
     LCDGotoXY(1,1);
	LCDWriteString("Gia tri U= ");							// Display string
	LCDData(Digit[2]+0x30);
	LCDData('.');						// Display first digit
	LCDData(Digit[1]+0x30);								// Display second digit
	LCDData(Digit[0]+0x30);	
    
     } 
      }
   }

