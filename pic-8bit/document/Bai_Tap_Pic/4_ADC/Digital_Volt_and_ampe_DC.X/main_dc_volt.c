#include <xc.h>
#include"adc_thay_hai.h"
#include"config.h"
#include"lcd.h"

unsigned int voltage ,ampe  ;

void main(void) 
{    
    ADC_Init();
    
    LCD_Init();
    
    while(1)
    {
        voltage = ADC_Read(0);
        voltage = (unsigned int)(voltage*4.888); 

        ampe = ADC_Read(1);
        ampe = (unsigned int)( (ampe*4.888)/0.47 );
            
        LCD_Set_Cursor(1,1);
        LCD_Write_String("U = ");
        LCD_Write_Number(voltage/1000);
        LCD_Write_Number((voltage%1000)/100);
        LCD_Write_Char('.');
        LCD_Write_Number((voltage%100)/10);
        LCD_Write_Number(voltage%10);
        LCD_Write_String("  V");
 
        LCD_Set_Cursor(2,1);
        LCD_Write_String("I = ");
        LCD_Write_String("0.");
        LCD_Write_Number(ampe);
        LCD_Write_String("  A");
    }
    return;
}
