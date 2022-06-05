#include "button.h"

extern unsigned int value;
extern unsigned int num ;
extern int mode_led_single;
extern int mode_led_7seg;

unsigned char pre_kb1,pre_kb2,pre_kb3; //present-hien tai

int mode_button = 0;

void set_case();

void pressButton()
{
	if(!kb1)
		pre_kb1=1;
	if(pre_kb1 && kb1)
	{
		pre_kb1 = 0;
		
		//do thing
		mode_button = 1;
		resetLedSingle();
		//end do thing
	}
	
	if(!kb2)
		pre_kb2=1;
	if(pre_kb2 && kb2)
	{
		pre_kb2 = 0;
		
		//do thing
		mode_button = 2;
		num=90;
		//end do thing
	}
	
	if(!kb3)
		pre_kb3=1;
	if(pre_kb3 && kb3)
	{
		pre_kb3 = 0;
		
		//do thing
		mode_button = 3;
		//end do thing
	}
	
	set_case();
}

void set_case()
{
	
	
	if(mode_button == 1)
	{
		TR0 = 1;//turn on timer 0
		mode_led_single = 1;
	}
	
	else if(mode_button == 2)
	{
		TR0 = 1;//turn on timer 0
		mode_led_7seg = 1;
	}
	
	else if(mode_button == 3)
	{
		TR0 = 0;//turn off timer0
		
		mode_led_single = 0;
		mode_led_7seg = 0;
		
		turnOff_7Seg();
		turnOffLedSingle();
		resetLedSingle();
	}	
	
}

