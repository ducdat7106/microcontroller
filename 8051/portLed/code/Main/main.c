#include "main.h"

#include "var.h"


void main()	
{
	while(1)
	{
		blink_ledx(3);
		delay_ms(1000);
		blink_ledx(1);
		delay_ms(1000);
	}
}