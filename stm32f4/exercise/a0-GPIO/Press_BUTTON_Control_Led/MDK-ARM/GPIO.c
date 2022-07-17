#include <GPIO.h>

void Bink_Led(int value, char ch[])
{
	if(value == 1)
	{
		if(strcmp("ON", ch) == 0)
			led1_on;
		else if(strcmp("OFF", ch) == 0)
			led1_off;
	}
	else if(value == 0)
	{
		if(strcmp("ON", ch) == 0)
			led2_on;
		else if(strcmp("OFF", ch) == 0)
			led2_off;
	}
	
	HAL_Delay(1000);
		
}



