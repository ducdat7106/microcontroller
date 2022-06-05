#include "button.h"

extern unsigned int value;
extern unsigned int num ;

unsigned char pre_kb1,pre_kb2,pre_kb3; //present-hien tai

unsigned int time_delay = 200;

int mode_button = 0;

void set_case();

void pressButton()
{
	if(kb1)
		pre_kb1=1;
	if(pre_kb1 && !kb1)
	{
		pre_kb1 = 0;
		
		//do thing
		mode_button=1;
		num=110;//110
		
		//end do thing
	}
	
	if(kb2)
		pre_kb2=1;
	if(pre_kb2 && !kb2)
	{
		pre_kb2 = 0;
		
		//do thing
		mode_button = 2;
		num=900;//900
		
		//end do thing
	}
	
	if(kb3)
		pre_kb3=1;
	if(pre_kb3 && !kb3)
	{
		pre_kb3 = 0;
		
		//do thing
		mode_button = 0;
		
		//end do thing
	}
	
	set_case();
}

void set_case()
{
	if(mode_button ==0 )
	{
		TR0 = 0;//turn off timer0
		turnOff();
	}
	
	else if(mode_button == 1)
	{
		TR0 = 1;//turn on timer 0
		if(value>=time_delay)
		{
			num++;
			if(num>=910)
			num=900;//910
		}	
	}
	
	else if(mode_button == 2)
	{
		TR0 = 1;//turn on timer 0
		if(value>=time_delay)
		{
			num--;
			if(num<=110)
			num=110;//110
		}	
	}
	
	if(value>=time_delay)
	{
		value=0;
	}
}

