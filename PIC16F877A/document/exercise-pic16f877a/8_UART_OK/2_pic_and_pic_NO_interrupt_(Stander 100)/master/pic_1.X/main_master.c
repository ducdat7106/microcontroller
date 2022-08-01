/*
 * File:   main_master.c
 * Author: Nguyen Duc Dat
 *
 * Created on 9 December, 2021, 2:57 AM
 */
#include <xc.h>
#include <stdint.h>

#include "config.h"
#include "lcd.h"
#include"uart_pic_pic.h"

#define Send RB2

int i=0;

void main(void)
{
    ADCON1 = 0x07;
    UART_Init(19200); // Initialize The UART in Master Mode @ 9600bps
    
    LCD_Init();
   
    char w_data[] ={0x66, 0x04, 0x03, 0x11, 0x67};
    char r_data[10];
    
    TRISB = 0x07; // RB0, RB1 & RB2 Are Input Pins (Push Buttons)
    TRISD = 0x00; // Output Port (4-Pins)
    PORTD = 0x00; // Initially OFF
    
    while(1)
    {
        if (Send == 1) // Send The Current Data Value Via UART
        {
            while(Send == 1);
            for(int y=0; y<6; y++)
            {
                UART_Write_Char(w_data[y]);
                __delay_ms(250);
            }
        }
        LCD_Set_Cursor(1,1);
        LCD_Write_String("T");
        
        LCD_Set_Cursor(1,2);
       
        for(int i=0; w_data[i]!='\0';i++)
        {
           LCD_Write_Number(w_data[i]);
           LCD_Write_String(" ");
        }
        
        if(UART_Data_Ready())
        {
           
            r_data[i] = UART_Read_Char();
            i++;
            if(i>5)
                i=0;
        }
           
        __delay_ms(100);
        LCD_Set_Cursor(2,1);
        LCD_Write_String("T");
        
        LCD_Set_Cursor(2,2);
       
            for(int v=0; v<6;v++)
            {
               LCD_Write_Number(r_data[v]);
               LCD_Write_String(" ");
            }   
    }
    return;
}