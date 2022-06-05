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
		//xung_test = !xung_test;
		value++;
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
				count_s=0;
				calculator_number(num);
			}
		}
}