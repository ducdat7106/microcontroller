#include "Led7Seg.h"

//code led 7 seg
unsigned char Number[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF};

unsigned char tram, chuc, dvi;
extern unsigned char digit;

void calculator_number(unsigned int number)
{
	tram = number/100;
	chuc = (number%100)/10;
	dvi = number%10;
}


void display_number_define_using_delay(unsigned int number)
{
	calculator_number(number);
	
	Led_7Seg = Number[tram];
	Control_Led1 = 0;
	delay_ms(2);
	Control_Led1 = 1;
	
	Led_7Seg = Number[chuc];
	Control_Led2 = 0;
	delay_ms(2);
	Control_Led2 = 1;
	
	Led_7Seg = Number[dvi];
	Control_Led3 = 0;
	delay_ms(2);
	Control_Led3 = 1;
}

/*
moi 1s se tang so len 1 lan

ma trong "ham display_number_define" co delay 8 ms

-->thoi gian vong lap i = 1000ms/8ms = 125 lan
*/
void display_number_from_x_to_y_after_1s(unsigned int x, unsigned int y)
{
	unsigned int i, k;
	
	if(x<y)
	{
		for(k=x; k<=y; k++)
		{			
			for(i=0; i<125; i++)
				display_number_define_using_delay(k);	
		}
	}
	else if(x>y)
	{
		for(k=x; k>=y; k--)
		{
			for(i=0; i<125; i++)
				display_number_define_using_delay(k);
		}
	}
}



void display_led7seg_using_timer()
{
	Led_7Seg = Number[10];//turn off all led 7 seg
	switch(digit)
	{
		case 0:
			Control_Led1 = 0; Control_Led2 = 1; Control_Led3 = 1;
			Led_7Seg = Number[tram];
			break;
		case 1:
			Control_Led1 = 1; Control_Led2 = 0; Control_Led3 = 1;
			Led_7Seg = Number[chuc];
			break;
		case 2:
			Control_Led1 = 1; Control_Led2 = 1; Control_Led3 = 0;
			Led_7Seg = Number[dvi];	
	}
}

void turnOff()
{
	Control_Led1 = 1; Control_Led2 = 1; Control_Led3 = 1;
	Led_7Seg = Number[10]; //turn off led
}