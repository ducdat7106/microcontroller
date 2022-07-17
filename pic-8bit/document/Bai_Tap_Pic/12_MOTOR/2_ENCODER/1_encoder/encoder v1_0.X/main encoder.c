/*
 * File:   main encoder.c
 * Author: Nguyen Duc Dat
 *
 * Created on 14 December, 2021, 2:04 AM
 */

#include"config.h"
#include<stdio.h>
#include"lcd.h"

#define xungA PORTBbits.RB0 //xung a noi vao RB4
#define xungB PORTBbits.RB5 //xung B noi vao RB5

#define tris_xungA TRISBbits.TRISB0
#define tris_xungB  TRISBbits.TRISB5

#define led PORTAbits.RA3
#define tris_led TRISAbits.TRISA3

#define Hight 1 //muc cao
#define Low 0 //muc thap

#define thuan 1 // chieu thuan
#define nghich 0 // chieu nghich
#define dung 2  //khong quay

#define khong_quay 0 // khong quay
#define quay    1//quay
char chieu_quay;
char trang_thai_chuyen_dong;


unsigned int u32NumberOfCounterOver=0;
unsigned int NumberOfTick=0;
float fFrequency = 0;
char str[30];


void ser_irs_rb0()
{
    INTEDG = 1;//ngat canh len
    GIE=1;
    INTE = 1;
    INTF = 0;
}

void timer1_config()
{
    GIE=1;
    PEIE=1;
    TMR1IE=1;
    TMR1IF=0;
    
    TMR1CS=0;// internal clock(Fosc/4) --> ko phai dem xung
    
    T1CKPS0=0;//1:1
    T1CKPS1=0;
}


void __interrupt() irs()
{
    if(INTF&&INTE)
    {        
        if(xungB == Low)
        {
            chieu_quay = thuan;
        }
        else if(xungB == Hight)
        {
            chieu_quay = nghich;
        }
        INTF = 0;
    }
    
    if(TMR1IE && TMR1IF)
    {
        u32NumberOfCounterOver++;
        TMR1IF=0;
    }
    
}



void main(void) 
{
    ADCON1  = 0X07;
    
    tris_xungB = 1;
    
    tris_led = 0;
    led=1;
    
    ser_irs_rb0();//cau hinh mgat ngoai RB0
    timer1_config();// cau hinh timer1
    
    LCD_Init();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("do encoder");
    __delay_ms(1000);
    LCD_Clear();
    
    while(1)
    {
        TMR1H=0;//xoa gia tri TIMER1
        TMR1L=0;
        while(RB0==1);
        while(RB0==0);
        TMR1ON=1;
        while(RB0==1);
        while(RB0==0);
        TMR1ON=0;
        
        NumberOfTick = (TMR1H<<8) | TMR1L;
        
        fFrequency = 5000000.0/(NumberOfTick+u32NumberOfCounterOver*65536);
        
        sprintf(&str[0], "%f", fFrequency);
        LCD_Set_Cursor(1,1);
        LCD_Write_String(&str[0]);
        
        u32NumberOfCounterOver = 0;
        //led = chieu_quay; // xuat ra cong RD7 chieu quay cua Encoder 
        
        LCD_Set_Cursor(2,1);
        if(chieu_quay == thuan)
        {
            LCD_Write_String("thuan");
        }
        else if(chieu_quay == nghich)
        {
            LCD_Write_String("nghich");
        }
    }
     return;
}
