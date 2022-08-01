/*
 * File:   main_led_7seg.c
 * Author: DAT PC
 *
 * Created on 25 January, 2022, 4:22 AM
 */


#include <xc.h>
#include "config.h"
#include "led_7seg.h"

#define button_up PORTBbits.RB4
#define button_down PORTBbits.RB5

#define tris_button_up TRISBbits.TRISB4
#define tris_button_down TRISBbits.TRISB5

void Config_Init();

void main(void) {
    
    int value = 4;
    int i=0;
    
    Config_Init();
    
    while(1){
        if(button_up == 0){
            while(button_up == 0);
            value++;
        }
        if(button_down == 0){
             while(button_down == 0);
            value--;
        }
        if(i==10)
            Led_7seg_Display(value);
        i++;
        if(i>10)
            i=0;
    }
    return;
}


void Config_Init(){
    ADCON1 = 0x06;
    
    tris_button_up = tris_button_down = 1;
    Led_7seg_Init();
    
}