/*
 * File:   main slave.c
 * Author: Nguyen Duc Dat
 *
 * Created on 12 December, 2021, 3:05 PM
 */
#include <xc.h>
#include<stdint.h>
#include<string.h>

#include"config.h"
#include"lcd.h"
#include"uart_pic_pic.h"

#define LED PORTAbits.RA0
#define TRIS_LED TRISAbits.TRISA0

char w_data[] ={0x45, 0x46, 0x47, 0x48, 0x49};
char r_data[10];

int a=0;

void main(void) 
{
    ADCON1 = 0x07;//disable adc
    
    TRIS_LED = 0;//as output
    LED = 1;//turn off
    
    TRISB0 =1;
    
    UART_Init(19200);
    
    LCD_Init();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("LCD_UART");
    //__delay_ms(500);
    LCD_Clear();
    
    while(1)
    {   
        if(RB0 == 1)
        {
            while(RB0 == 1);
            for(int t=0; t<=(strlen(w_data)); t++)
            {
                UART_Write_Char(w_data[t]);
                __delay_ms(150);
            }
        }
        
        if(UART_Data_Ready())
        {
            r_data[a++] = UART_Read_Char();
            if(a>5)
                a=0;
        }
        LCD_Set_Cursor(1,1);
        LCD_Write_String("T");
        
        LCD_Set_Cursor(1,2);
        ///*
        for(int k=0; w_data[k] != '\0'; k++)
        {
            LCD_Write_Number(w_data[k]);
            LCD_Write_String(" ");
        }       
         LCD_Set_Cursor(2,1);
        LCD_Write_String("R");
        
        LCD_Set_Cursor(2,2);

            for(int k=0; k<6; k++)
            {
                LCD_Write_Number(r_data[k]);
                LCD_Write_String(" ");
            }      
    }
    return;
}

void transmit_data(char *data)
{
    
}