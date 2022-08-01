/*
 * File:   main_tao_xung.c
 * Author: Nguyen Duc Dat
 *
 * Created on 14 December, 2021, 8:37 AM
 */
#include <xc.h>
#include<stdint.h>

#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = ON       
#pragma config BOREN = ON       
#pragma config LVP = ON         
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#define xung PORTEbits.RE0  //chan phat xung RD0
#define tris_xung TRISEbits.TRISE0

#define button PORTBbits.RB0
#define tris_button TRISBbits.TRISB0

unsigned int i=0;


void UART_TX_Init( unsigned long uart_baudRate );
void UART_Write_Char(char data);
void UART_Write_String(char *text);

/*
    Delay Calculations for 1.5ms @20Mhz with Prescalar as 32:
    RegValue = 256-(Delay * Fosc)/(Prescalar*4))
    = 256-((1.5ms * 20*10^6)/(32*4)) = 256-234=22;
 
 */
void tao_xung_T_3ms()
{
    PS2=1; PS1=0; PS0=0;//1 : 32
    
    PSA=0;
    T0SE=0;
    T0CS=0;
    
    GIE=1; //Enable Global Interrupt
    
    TMR0=22;       // Load the time value for 1.5ms delay
    
}

void time1()//10ms xay ra ngat 1 lan
{
    TMR1 = 15535;
    T1CONbits.T1CKPS1 = //1:4
    T1CONbits.T1CKPS0 = 0;
    
    T1CONbits.TMR1CS = 0;
    
    T1CONbits.T1SYNC = 1;
    T1CONbits.TMR1ON = 1;
    
    TMR1IE=1;
    PEIE=1;
    GIE=1;
}

void __interrupt() ISR()
{
    if(TMR0IE&&TMR0IF)
    {
        xung=~xung;//dao trang thai
        TMR0 = 22; /*Load the timer Value, (Note: Timer value is 101 instaed of 100 as the
                    TImer0 needs two instruction Cycles to start incrementing TMR0) */
        TMR0IF=0; // Clear timer interrupt flag
    }
    
    if(TMR1IE && TMR1IF)
    {
        TMR1=15535;
        i++;
        if(i>=200)// moi  2s  se vao if
        {
            i=0;
            UART_Write_String("Reading\r"); //gui du lieu "Reading" qua uart
        }
        
        TMR1IF=0;
    }
}

void main(void) 
{
    ADCON1 = 0x07;// all PIN is digital
    
    tris_xung = 0;// as output
    xung = 0;//turn off
    
    tris_button = 1;// as input
    
    tao_xung_T_3ms();//khoi tao timer 0
    
    time1();
           
    UART_TX_Init(19200);// khoi tao uart voi toc do 19200
   
    while(1)
    {
        //thoi gian ton tai xung  1 m s
        if(button == 0)
        {
            while(button == 0);
            TMR0IE=1; ;
            __delay_ms(1);//thoi gian ton tai xung 1 ms
            TMR0IE=0; 
            xung =0;
        }
        //------------------------------       
    }
    return;
}

void UART_TX_Init( unsigned long uart_baudRate )
{
  uint16_t x;
  x = (_XTAL_FREQ - uart_baudRate*64)/(uart_baudRate*64); // Low Baud Rate
  if(x>255)  
  {
    x = (_XTAL_FREQ - uart_baudRate*16)/(uart_baudRate*16); // High Baud Rate
    BRGH = 1;
  }
  if (x<=255)
  {
    SPBRG = x;  //Writing SPBRG Register
  }
  //--[ Enable The Ascynchronous Serial Port ]--
  SYNC = 0;
  SPEN = 1;
  //--[ Set The RX-TX Pins to be in UART mode (not io) ]--
  TRISC6 = 1;   // As stated in the datasheet
  TRISC7 = 1;   // As stated in the datasheet
  TXEN = 1;     // Enable UART Transmission
}
 
void UART_Write_Char(char data)
{
  while(!TRMT);
  TXREG = data;
}
 
void UART_Write_String(char *text)
{
  uint16_t i;
  for(i=0;text[i]!='\0';i++)
    UART_Write_Char(text[i]);
}