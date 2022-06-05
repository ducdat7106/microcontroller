#include "main.h"
#include "var.h"


void main()	
{
	initTimer0(1);
	
	while(1)
	{
		P0_0 = !P0_0;
		delay_ms_timer0(1000);
	}
}
