#ifndef _LED7SEG_H_
#define _LED7SEG_H_

#include "main.h"

//led 7seg anode, power
#define Led_7Seg P0	

#define Control_Led1 P2_0 
#define Control_Led2 P2_1
#define Control_Led3 P2_2 

//led 7seg
void calculator_number(unsigned int number);

void display_number_define_using_delay(unsigned int number);
void display_number_from_x_to_y_after_1s(unsigned int x, unsigned int y);

void display_led7seg_using_timer();

void turnOff();


#endif