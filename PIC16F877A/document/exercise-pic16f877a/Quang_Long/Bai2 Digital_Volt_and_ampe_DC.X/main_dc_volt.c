#include <xc.h>
#include"adc_thay_hai.h"
#include"config.h"
#include"lcd.h"

//_XTAL_FREQ =    16000000

#define LED_VOLT PORTBbits.RB0
#define LED_AMPE PORTBbits.RB1
#define TRIS_LED_VOLT TRISBbits.TRISB0
#define TRIS_LED_AMPE TRISBbits.TRISB1

unsigned int voltage ,ampe;
unsigned int count = 0;

void GPIO();
void time1();
void compe();
void do_luong();
void hien_thi();

void __interrupt()  ISR()//10 m s
{
    if(TMR1IE && TMR1IF)
    {
        count++;
        if(count>=100)
            count=0;
        
        compe();
        
        TMR1=55536;
        TMR1IF=0;
    }
}


void main(void) 
{    
    int i=0;
    
    ADC_Init();
    
    time1();
     
    GPIO();
    
    LCD_Init();
    
    while(1)
    {  
       
        do_luong();
        
        hien_thi();
    }
    return;
}

void GPIO()
{
    TRIS_LED_VOLT = TRIS_LED_AMPE = 0;//as output
    LED_VOLT = LED_AMPE = 1;//as turn off
}

void time1()
{
    T1CONbits.T1CKPS1 = 1;//1:4
    T1CONbits.T1CKPS0 = 0;
    
    T1CONbits.TMR1CS = 0;
    
    T1CONbits.T1SYNC = 1;
    T1CONbits.TMR1ON = 1;
    
    TMR1IE=1;
    PEIE=1;
    GIE=1;
    
    TMR1 = 64536;
}

void compe()
{
    if(voltage<1500)
        LED_VOLT = 1;
    
    if(voltage >= 1500)
    {
        if(count<=50)
            LED_VOLT = 0;
        else if(count>50)
            LED_VOLT = 1;
    }
        
    if(ampe <750)
        LED_AMPE = 1;
    
    if(ampe >=750)
    {
        if(count<=50)
            LED_AMPE = 0;
        else if(count>50)
            LED_AMPE = 1;
    }      
}

void do_luong()
{
    voltage = ADC_Read(0);
    voltage = (unsigned int)(voltage*4.888); 

    ampe = ADC_Read(1);
    ampe = (unsigned int)( (ampe*4.888)/0.47 );
}

void hien_thi()
{
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