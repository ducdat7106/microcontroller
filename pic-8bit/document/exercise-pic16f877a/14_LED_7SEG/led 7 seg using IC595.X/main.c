/*
 * File:   main.c
 * Author: DAT PC
 *
 * Created on 25 January, 2022, 5:58 AM
 */

#include <xc.h>
#include "config.h"
#include <pic16f877a.h>


#define button_up PORTBbits.RB4
#define button_down PORTBbits.RB5

#define tris_button_up TRISBbits.TRISB4
#define tris_button_down TRISBbits.TRISB5


#define enable_led1 PORTCbits.RC4
#define enable_led2 PORTCbits.RC5
#define enable_led3 PORTCbits.RC6
#define enable_led4 PORTCbits.RC7

#define tris_enable_led1 TRISCbits.TRISC4
#define tris_enable_led2 TRISCbits.TRISC5
#define tris_enable_led3 TRISCbits.TRISC6
#define tris_enable_led4 TRISCbits.TRISC7


#define data_pin PORTBbits.RB1 //DS    shift  data
#define clock_pin PORTBbits.RB0 //SH_CP
#define latch_pin PORTBbits.RB2 //ST_CP
#define tris_data_pin TRISBbits.TRISB1
#define tris_clock_pin TRISBbits.TRISB0
#define tris_latch_pin TRISBbits.TRISB2

/*khai bao bien toan cuc*/                                   
unsigned int j,nghin,tram,chuc,donvi ;
unsigned int Value_Display = 54;

char Number_7Seg[]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

/*khai bao ham con*/
void Config_Init();
void Test_Button();
void Write_Data(unsigned int number);
void Scan_7Seg();//quet led 7 doan


/*ham chinh xu ly*/
void main(void) {
    
    Config_Init();
    
    while(1){
        /* kiem tra phim nhat*/
        Test_Button();
        /*tien hanh quet led*/
        Scan_7Seg(); 
    }
    
    return;
}

void Config_Init(){
    ADCON1 = 0x06;
    
    tris_data_pin=0;
    tris_clock_pin=0;
    tris_latch_pin=0;
    
    data_pin=1;
    clock_pin=1;
    latch_pin=1;
    
    tris_enable_led1 = 0;
	tris_enable_led2 = 0;
	tris_enable_led3 = 0;
	tris_enable_led4 = 0;
	
	enable_led1 = 1;
	enable_led2 = 1;
	enable_led3 = 1;
	enable_led4 = 1;
}


/*ham con dich bit data*/
void Write_Data(unsigned int number){
    for(j = 0x80; j > 0x00; j = j >> 1){ //0x80 = 10000000    
          if(number & j){
            data_pin=1; // xung cao
          }
          else
          {
            data_pin=0; //xung thap
          }
          /*tao xung clock day data*/
          clock_pin=1;
          clock_pin=0;
    }
   /*tao xung ket thuc day data*/
    latch_pin=1;
    latch_pin=0;
}

/*ham con kiem tra nut nhan*/
void Test_Button()
{    
    if(button_up == 0) {
        while(button_up == 0);
        Value_Display++;
        if(Value_Display > 9999)
            Value_Display = 9999;
    }

    if(button_down == 0) {
        while(button_down == 0);       
        Value_Display--;
        if(Value_Display < 1)
            Value_Display = 1;
    }
    
    nghin = Value_Display/1000;          // hang  nghin
    tram  = (Value_Display %1000)/100;  // hang tram
    chuc  = (Value_Display%100)/10;      // hang chuc
    donvi = Value_Display%10;            // hang don vi
}
void Scan_7Seg(){
    /*quet led thu nhat*/
    enable_led1=1;                      
    Write_Data( Number_7Seg[nghin] );
    __delay_ms(1);
    enable_led1=0; 
    
    /*quet led thu hai*/
    enable_led2=1;   
    Write_Data( Number_7Seg[tram] );
    __delay_ms(1); 
    enable_led2=0; 
    
     /*quet led thu ba*/
    enable_led3=1;  
    Write_Data( Number_7Seg[chuc]);                    
    __delay_ms(1);
    enable_led3=0;  
    
     /*quet led thu tu*/     
    enable_led4=1;                     
    Write_Data( Number_7Seg[donvi]);                     
    __delay_ms(1);
    enable_led4=0;
}


