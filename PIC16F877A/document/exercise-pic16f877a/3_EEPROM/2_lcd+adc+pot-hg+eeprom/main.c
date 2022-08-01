/*
 * File:   main.c
 * Author: Nguyen 
 *
 * Created on 17 November, 2021, 7:36 PM
 */
 
#include <xc.h>
#include <stdlib.h>
#include"config.h"
#include"adc.h"
#include"lcd.h"
#include"eeprom.h"

int main()
{
    int adc=0; //Variable to read ADC value
    int a1,a2,a3,a4; //Variable to split ADC value into char
    
    int Sadc=0; //Variable to read ADC value
    int Sa1,Sa2,Sa3,Sa4; //Variable to split ADC value into char
    
    TRISD = 0x00; //PORTD declared as output for interfacing LCD
    TRISA4 =1; //AN4 declared as input
    TRISB0  = 1;
    //OPTION_REG=0b00000000;
    ADC_Initialize();
    Lcd_Start();
    Lcd_Clear();
    
    while(1)
    { 
        adc=ADC_Read(4); //Read ADC
        
         //**Display ADC**//
        a1 = (adc/1000)%10;
        a2 = (adc/100)%10;
        a3 = (adc/10)%10;
        a4 = (adc/1)%10;
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("ADC:");
        Lcd_Print_Char(a1+'0');
        Lcd_Print_Char(a2+'0');
        Lcd_Print_Char(a3+'0');
        Lcd_Print_Char(a4+'0');
        
      //**Display SADC**//
        Sa1 = (Sadc/1000)%10;
        Sa2 = (Sadc/100)%10;
        Sa3 = (Sadc/10)%10;
        Sa4 = (Sadc/1)%10;
        Lcd_Set_Cursor(2,1);
        Lcd_Print_String("Saved ADC:");
        Lcd_Print_Char(Sa1+'0');
        Lcd_Print_Char(Sa2+'0');
        Lcd_Print_Char(Sa3+'0');
        Lcd_Print_Char(Sa4+'0');
        /*These devices have 4 or 8K words of
          program Flash, with an address range from 0000h to
          1FFFh for the PIC16F877A*/
        
        if (RB0==0)
        {
            EEPROM_Write(0,adc);
        }
        
        Sadc = (int)EEPROM_Read(0);
        
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("ADC:");
        
    }
    return 0;
}
