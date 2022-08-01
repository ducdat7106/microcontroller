/*
 * File:   main.c
 * Author: Nguyen Duc Dat
 *
 * Created on 3 December, 2021, 10:12 AM
 */


#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 20000000
#include <xc.h>
// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)

#define ds PORTCbits.RC0
#define st PORTCbits.RC1
#define sh PORTCbits.RC2
unsigned char khung_du_lieu[32];
unsigned char socot,sohang,tocdo,maled;
unsigned char g,h,a;

//------------------------------------------------------ du lieu cot luu vao ROM------------------------------------------
const unsigned char codedu_lieu_cot[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0xff,0x60,0x30,0x18,0x0C,0xFF,0xFF,///////////////N
0x00,0x00,0x00,
0x7E,0xFF,0xC3,0xC3,0xCB,0xCB,0xEF,0x6E,///////////////G
0x00,0x00,0x00,
0x7E,0xFF,0xC3,0xC3,0xC3,0xC3,0xFF,0x7E,//////////////O
0x00,0x00,0x00,
0x7E,0xFF,0xC3,0xC3,0xC3,0xC3,0xEF,0x6E,//////////////C
0x00,0x00,0x00,
0xff,0xff,0x03,0x03,0x03,0x03,0x03,0x03,///////////////L
0x00,0x00,0x00,
0x1f,0x3f,0x6c,0xcc,0xcc,0x6c,0x3f,0x1f,///////////////A
0x00,0x00,0x00,
0xff,0xff,0x60,0x30,0x30,0x60,0xff,0xff,//////////////M
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					 };
void tonghop(void);
void delay_ms(unsigned int ms);
void load(unsigned int u);
void main(void)
{
  TRISD = 0X00;
  TRISC = 0X00;
  PORTD=0xff;
  PORTC=0x00;
  while(1)
   {
     tonghop();
   }
}


void delay_ms(unsigned int ms)
{
  unsigned int i;
  unsigned char j;
  for(i=0;i<ms;i++)
     for(j=0;j<120;j++);
}

void load(unsigned int u)
{
  unsigned char i;
  for(i=0;i<32;i++)
   {
     khung_du_lieu[i]=codedu_lieu_cot[u];
	 u++;
   }
}

void tonghop(void)
{
    unsigned char i;
    for(socot=0;socot<106;socot++) //73+32=105 la so phan tu du_lieu_cot
	  {
	    load(socot);
	    for(tocdo=0;tocdo<10;tocdo++)// delay
	      {
		     a=0xfe;
	         h=0x80;
		     for(sohang=0;sohang<8;sohang++)
			   {
			     st=0;
			     for(i=0;i<32;i++)
				   {
				     sh=0;
				     g=khung_du_lieu[i];
					 if((g&h)==h) ds=1;
					 else         ds=0;
					 sh=1;
				   }
				 st=1;
				 h=h>>1;
				 PORTD=a;
				 delay_ms(1);
				 PORTD=0xff;
				 a=(a<<1)+1;
			   }
			}
	    }
}

/*https://xcvn.blogspot.com/2016/05/bai-38-led-matrix-8x32-pic16f877a-xc8.html*/