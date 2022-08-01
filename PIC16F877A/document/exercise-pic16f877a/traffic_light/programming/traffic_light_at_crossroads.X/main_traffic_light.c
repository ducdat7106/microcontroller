/*
 * File:   main_traffic_light.c
 * Author: NGUYEN DUC DAT
 *
 * Created on 22 January, 2022, 5:47 AM
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define LED_7SEG PORTD
#define TRIS_LED_7SEG TRISD


#define T1 PORTBbits.RB0     //transistor 1 for led_7seg 1
#define T2 PORTBbits.RB1     //transistor 2 for led_7seg 2
#define T3 PORTBbits.RB2     //transistor 3 for led_7seg 3
#define T4 PORTBbits.RB3     //transistor 4 for led_7seg 4

#define TRIS_T1 TRISBbits.TRISB0
#define TRIS_T2 TRISBbits.TRISB1
#define TRIS_T3 TRISBbits.TRISB2
#define TRIS_T4 TRISBbits.TRISB3


#define NORMAL PORTAbits.RA0
#define RUSH_HOUR PORTAbits.RA1
#define NIGHT PORTAbits.RA2
#define RAIN_SENSOR PORTAbits.RA3

#define TRIS_NORMAL TRISAbits.TRISA0
#define TRIS_RUSH_HOUR TRISAbits.TRISA1
#define TRIS_NIGHT TRISAbits.TRISA2
#define TRIS_RAIN_SENSOR TRISAbits.TRISA3


#define X1 PORTCbits.RC0
#define V1 PORTCbits.RC1
#define D1 PORTCbits.RC2
#define X2 PORTCbits.RC3
#define V2 PORTCbits.RC4
#define D2 PORTCbits.RC5

#define TRIS_X1 TRISCbits.TRISC0
#define TRIS_V1 TRISCbits.TRISC1
#define TRIS_D1 TRISCbits.TRISC2
#define TRIS_X2 TRISCbits.TRISC3
#define TRIS_V2 TRISCbits.TRISC4
#define TRIS_D2 TRISCbits.TRISC5

#define bat 1 //sang
#define tat 0


//led anot chung
char number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

int num1,donvi1,chuc1;
int num2,donvi2,chuc2;

int macdinh=1;

int normal_state=1;
int night_state=1;
int rain_stare=1;
int rush_hour_state=1;


void init_cofig();
void hienThi();
void rain_mode(int  value_ms);
void normal_mode(int value);
void rush_hour_mode(int digit);
void night_mode(int value);


void main(void) 
{
    init_cofig();
    
    while(1)
    {
        if(NORMAL != macdinh)
        if( !NORMAL )
            normal_state=0;
        macdinh=NORMAL;
        
        if(RUSH_HOUR != macdinh)
        if( !RUSH_HOUR )
            rush_hour_state=0;
        macdinh=RUSH_HOUR;
        
        if(NIGHT != macdinh)
        if( !NIGHT )
            night_state=0;
        macdinh=NIGHT;
        
        if(RAIN_SENSOR != macdinh)
        if( !RAIN_SENSOR )
            rain_stare=0;
        macdinh=RAIN_SENSOR;
        
        if(!normal_state )
            normal_mode(30);
        
        if(rush_hour_state)
            rush_hour_mode(60);
        
        if(!night_state)
            rain_mode(500);
        
        if(!night_state)
            night_mode(500);   
                    
    }
    //return 0;
}

void init_cofig(){
    ADCON1 = 0x06;
    
    TRIS_NORMAL=1;
    TRIS_RUSH_HOUR=1;
    TRIS_NIGHT=1;
    TRIS_RAIN_SENSOR=1;
    
    TRIS_LED_7SEG = 0x00;
    LED_7SEG = 0xff;
    
    TRIS_T1 = 0;
    TRIS_T2 = 0;
    TRIS_T3 = 0;
    TRIS_T4 = 0;  
    T1=T2=T3=T4=tat;
    
    TRIS_X1=0;
    TRIS_V1=0;
    TRIS_D1=0;
    TRIS_X2=0;
    TRIS_V2=0;
    TRIS_D2=0;
    X1=X2=V1=V2=D1=D2=tat;
}

void hienThi(){
    int count;
    
    for(count=0; count <50; count++){
        chuc1 = num1/10;
        donvi1 = num1%10;
        LED_7SEG = number[chuc1];
        T3 = bat;
        __delay_ms(50);
        T3 = tat;
        LED_7SEG = number[donvi1];
        T4 = bat;
        __delay_ms(50);
        T4 = tat;
        
        chuc2=num2/10;
        donvi2=num2%10;
        LED_7SEG = number[chuc1];
        T1 = bat;
        __delay_ms(50);
        T1 = tat;
        LED_7SEG = number[donvi1];
        T2 = bat;
        __delay_ms(50);
        T2 = tat;
    }
}

//che do mua: nhap nhay den vang
void rain_mode(int  value_ms){
    X1 = D1 = tat;
    X2 = D2 = tat;
    
    V1 = V2 = bat;
    for(int i=0; i<value_ms; i++)
        __delay_ms(1); //1 m s
    V1 = V2 = tat;
    for(int i=0; i<value_ms; i++)
        __delay_ms(1); //1 m s
}

void normal_mode(int value){
    int temp1 = 5;
    num1= value+temp1;//35
    num2= value;//30
    do{
        LED_7SEG = 0xFF;// turn off all led_7seg
        X1 = D2 = bat;
        V1 = D1 = tat;
        V2 = X2 = tat;
        hienThi();
        num1--;
        num2--;
    }while(num2 != 0);
    
    num1=num2=temp1;
    do{
        V1=D2=bat;
        D1 = X1 = tat;
        V2 = X2 = tat;
        hienThi();
        num1--;
        num2--;
    }while(num2 != 0);
    
    num1=value; //30              
    num2=value+temp1;//35
    do{
        LED_7SEG = 0xFF;// turn off all led_7seg
        X2 = D1 = bat;
        V1 = X1 = tat;
        V2 = D2 = tat;
        hienThi();
        num1--;
        num2--;
    }while(num1 != 0);
    
    num1=num2=temp1;
    do{
        V2=D1=bat;
        V1 = X1 = tat;
        D2 = X2 = tat;
        hienThi();
        num1--;
        num2--;
    }while(num1 != 0);
}

void rush_hour_mode(int digit){
    normal_mode(digit);
}

void night_mode(int value){
    rain_mode(value);
}

