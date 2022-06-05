#include "ledSingle.h"

unsigned char LHigh,LLow; //LHigh - Led High, LLow - Led Low 
unsigned int LRight, LLeft;
	
unsigned int temp=0,  run=0x0001;
unsigned int result = 0;

extern unsigned int value;

int reset=10;

void ouput16Led();
void turnOffLed();
void turnOnLed();

void ouput16Led()
{
	LHigh = result;
	LLow = result >> 8;
	
	Led_High = ~LHigh;
	Led_Low = ~LLow;
}

void turnOffLedSingle()
{
	Led_High = Led_Low = 0xFF;
}

void turnOnLed()
{
	Led_High = Led_Low = 0x00;
}

void resetLedSingle()
{
	result=0;
	temp=0;
	run = 0x8000; //cho xua
	reset = 0;
}

/*
void don_1led_sang_phai()
{
	for(i=0; i<16; i++)
	{
		run = 0x0001;
		for(j=i; j<16; j++)
		{
			result = temp|run;
			ouput16Led();
			
			run = run << 1;
		}
		temp = result;
	}
	temp = 0;
}
*/

void don_1led_sang_phai()
{
	  static int i=0, j=-1;
	
		if(reset == 0)
		{
			i=0; 
			j=-1;
			reset=10;
		}
	
		if(value%50==0)
		{
			j++;
			
			/////
			result = temp|run;
			ouput16Led();		
			run = run >> 1; // cho xua
			///
			
			if(j>15)
			{
				i++;
				j=i-1;
				run = 0x8000; //cho sua
				temp = result;
			}
			
			if(i>15)
			{
				i=0;
				j=-1;
				temp = 0;
			}
		}
}



/*
void don_1led_sang_trai()
{
	for(i=0; i<16; i++)
	{
		run = 0x8000;
		for(j=i; j<16; j++)
		{
			result = temp|run;
			ouput16Led();
			delay_ms(50);
			run = run >> 1;
		}
		temp = result;
	}
	temp = 0;
}

void don_2led_sang_phai()
{
	for(i=0; i<16; i++)
	{
		run = 0x0003;//000+0011
		for(j=i; j<8; j++)
		{
			result = temp|run;
			ouput16Led();
			delay_ms(50);
			run = run << 2;
		}
		temp = result;
	}
	temp = 0;
}

void don_2led_sang_trai()
{
	for(i=0; i<16; i++)
	{
		run = 0xC000;//1100+000
		for(j=i; j<8; j++)
		{
			result = temp|run;
			ouput16Led();
			delay_ms(50);
			run = run >> 2;
		}
		temp = result;
	}
	temp = 0;
}


void don_3led_sang_1led_phai()
{
	for(i=0; i<16; i++)
	{
		run = 0x0007;
		for(j=i; j<16; j++)
		{
				result = temp |run;
				ouput16Led();
				delay_ms(50);
				run = run << 1;
		}
		temp = result;
	}
	
	temp = 0; 
}


void don_3led_sang_1led_trai()
{
	for(i=0; i<16; i++)
	{
		run = 0xE000;
		for(j=i; j<16; j++)
		{
				result = temp |run;
				ouput16Led();
				delay_ms(50);
				run = run >> 1;
		}
		temp = result;
	}
	
	temp = 0; 
}

void led_2led_giua_sang_dan_ra()
{
	LRight = LLeft =0;
	
	for(i=0; i<8; i++)
	{
		LLeft = (LLeft <<1 ) + 0x01;
		LRight = (LRight >> 1) + 0x80;

		result =LLeft<<8;
		result |= LRight;
		
		ouput16Led();
		delay_ms(500);
	}
}

void led_2_ben_sang_dan_vao()
{
	LRight = LLeft =0;
	for(i=0; i<8; i++)
	{
		LLeft = (LLeft <<1 ) + 0x0001;
		LRight = (LRight >> 1) + 0x8000;
		result =LLeft|LRight;
		ouput16Led();
		delay_ms(500);
	}
}

void led_2_ben_tat_dan_vao()
{
	unsigned char LLLeft, LLRight;
	LLLeft=LLRight=0xFF;
	
	result = 0xFFFF;
	ouput16Led();
	delay_ms(500);
	
	for(i=0; i<8; i++)
	{
		LLLeft = (LLLeft>>1);
		LLRight = (LLRight<<1);
		
		result = LLLeft<<8;
		result |= LLRight;
		ouput16Led();
		delay_ms(500);
	}
}

void led_2led_giua_tat_dan_ra_2_ben()
{
	unsigned char LLLeft, LLRight;
	LLLeft=LLRight=0xFF;
	
	result = 0xFFFF;
	ouput16Led();
	delay_ms(500);
	
	for(i=0; i<8; i++)
	{
		LLLeft=(LLLeft<<1);
		LLRight = (LLRight>>1);
		
		result = LLLeft<<8;
		result |= LLRight;
		
		ouput16Led();
		delay_ms(500);
	}	
}
*/




