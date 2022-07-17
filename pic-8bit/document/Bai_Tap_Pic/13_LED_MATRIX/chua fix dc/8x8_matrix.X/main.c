/*
 * File:   main.c
 * Author: Nguyen Duc Dat
 *
 * Created on 3 December, 2021, 9:53 AM
 */
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4000000

#include <xc.h>
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
const unsigned char FontA[8] = {0xff,0x01,0x00,0xf6,0xf6,0x00,0x01,0xff}; 
// lay ma tu duoi len 8 - 4 - 2 - 1
// sang la 0 tat la 1
void main()
{
 unsigned char i;
 unsigned char cnt;
 unsigned char j;
    TRISB = 0X00;
    TRISD = 0X00;
 while(1)
 {
  for(i=0;i<7;i++)
  {
  PORTB = FontA[i];
  PORTD = 0x01<<i;
  __delay_ms(1);
  PORTD = 0x00;
  }           
    }
}


/*
 tham khao
 https://xcvn.blogspot.com/2016/04/led-matrix-8x8-pic16f877a-xc8.html
 */