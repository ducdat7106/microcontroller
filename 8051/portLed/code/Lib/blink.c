#include "blink.h"

void blink_ledx(int x)
{
		if(x == 10)
		{
			Led1 = 0x00;
			delay_ms(1000);
			Led1 = 0xFF;
			delay_ms(1000);
			
		}else{
			Led2 = 0x00;
			delay_ms(1000);
			Led2 = 0xFF;
			delay_ms(1000);
		}
}