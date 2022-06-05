#include "main.h"
#include "var.h"

void main()
{
	timer0_init();
	
	while(1)
	{
		pressButton();
	}
}



void do_thing_in_interrupt()
{
		value++;
		if(value >= 10000) //10s
				value =0;
		

		if(mode_led_7seg == 1)
		{
			if(value % time_delay_7seg == 0)
			{
				num--;
				if(num<=80)
					num=80;//80
			}	
			
			count++;
			if(count == 5) //5ms
			{
				count=0;
				display_led7seg_using_timer();				
				digit++;
				if(digit==3)
					digit=0;
				count_s++;
				if(count_s == 25)
				{
					count_s = 0;
					calculator_number(num);
				}
			}
		}
		
		if(mode_led_single == 1)
		{
			don_1led_sang_phai();
		}
		else 
		{
			resetLedSingle();
		}
		
}