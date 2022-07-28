/*
 * File:   main-uart.c
 * Author: Nguyen Duc Dat
 *
 * Created on 12 December, 2021, 6:04 PM
 */
#include <xc.h>
#include<stdio.h>

#include"config.h"
#include"uart send and get.h"
#include"lcd.h"

#define led PORTEbits.RE0
#define tris_led TRISEbits.TRISE0

#define b_up PORTBbits.RB0
#define b_down PORTBbits.RB1
#define b_write PORTBbits.RB2

#define tris_b_up TRISBbits.TRISB0
#define tris_b_down TRISBbits.TRISB1
#define tris_b_write TRISBbits.TRISB2

char r_data = 0;

void main(void) 
{
    ADCON1 = 0x07;
    
    tris_b_up = 1;//as input
    tris_b_down = 1;//as input
    tris_b_write = 1;//as input
    
    tris_led = 0;//as output
    led = 1;//turn off
    
    LCD_Init();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("LCD ECHO UART");
    __delay_ms(1000);
    LCD_Clear();
     
    
    UART_TX_AND_RX_Init(9600);
    __delay_ms(100);
    UART_Write_String("UART Module Initialized and active:\r");// Introductory Text
    __delay_ms(100);
    while(1)
    {
        /*
        UART_Write_Char('U');   //Send character U
        UART_Write_Char('A');   //Send character A
        UART_Write_Char('R');   //Send character R
        UART_Write_Char('T');   //Send character T
        UART_Write_Char('\r');  //Send carriage return for new line
        __delay_ms(1000);
        */
        
        if(UART_Data_Ready())   // if a character available
        {
            r_data = UART_Read_Char();
            UART_Write_Char(r_data);
        }
        
        if(r_data == '0')//If the user sends "0"    //r_data == 'A'  OK nho bat caps lock
        {
            led = 0;
            
            UART_Write_String("RED LED -> ON"); //Send notification to the computer 
            UART_Write_Char('\r');//ASCII value 10 is used for carriage return (to print in new line)
        }
        
        if(r_data == '1')//If the user sends "1"
        {
            led = 1; 
            UART_Write_String("RED -> OFF"); //Send notification to the computer      
            UART_Write_Char('\r');//ASCII value 10 is used for carriage return (to print in new line)
       
        }
        
        LCD_Set_Cursor(1,1);
        LCD_Write_String("RX:");
        LCD_Write_Char(r_data);
        
    }
    return;
}


void dieuKhienLedQuaMayTinh()
{
    
}

void guiDuLieuLenMayTinh()
{
    
}


//truyen nguoc lai ky tu vua nhan len may tinh
void receiver_after_transmit()
{
	if ( UART_Data_Ready() )  // if a character available
    {
      unsigned char c = UART_Read_Char();  // read from UART and store in 'c'
      UART_Write_Char(c);  // send 'c' via UART (return the received character back)
    }
    
    UART_Write_String("\r\n");  // start new line
}

void transmit_Number()
{
	char text[5];
	for (unsigned char i = 0; i < 21; i++)
	{
		sprintf(text, "%02u\r\n", i);
		UART_Write_String(text);
		__delay_ms(500);
	}
}
