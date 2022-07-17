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
unsigned int i;
char number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  

int main ()
{
    Tris_kb1=Tris_kb2=Tris_kb3=Tris_kb4=Input ;  
    Tris_Led=Out;
    Tris_d1=Tris_d2=Tris_d3=Tris_d4=Out;
    Tris_Led_7SEG=0;
    
	while(1)
	{   
       // Led=0;
        //    __delay_ms(1000);
       // Led=1;
      //  __delay_ms(1000);
        
        d1=0;d2=d3=d4=1;
        for(i=0;i<10;i++)
       {
    	Led_7SEG= number[i];
        __delay_ms(1000);
       }
        
      }
   }

