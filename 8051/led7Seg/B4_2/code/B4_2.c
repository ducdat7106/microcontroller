#include <REGX52.H>


//led single
#define Led P2

//led 7seg anode, power
#define Led_7Seg P0	

#define Control_Led1 P3_4 
#define Control_Led2 P3_5 
#define Control_Led3 P3_6 
#define Control_Led4 P3_7 

//button
#define b1 P1_0
#define b2 P1_1
#define b3 P1_2

int status=0;
//code led 7 seg
unsigned char Number[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

//config system
void config();

void delay_ms(unsigned int);

//led single
void sangDon();


//led 7seg
void display_number_define(unsigned int);
void display_number_from_x_to_y(unsigned int x, unsigned int y);

//button
void button();

void turnOff();

//interrupt
void config_EXT();

void main()
{
	config();
	
	while(1)
	{
		button();
	}
}

void config()
{
	turnOff();
	config_EXT();
}
	
void delay_ms(unsigned int t){
	unsigned int x, y;
	
	for(x=0; x<t; x++)
		for(y=0; y<123; y++);
}

void sangDon()
{
	unsigned int TTCD, TTDC;//TTCD la trang thai co dinh, TTDC la trang thai dich chuyen
	int i, j;
	
	TTCD = 0;
	for(i=8; i>0; i--)
	{
		TTDC = 0x01;
		for(j=0; j<i; j++)
		{			
			if(status != 1)
				break;
			
			Led = TTCD|TTDC;
			delay_ms(200);
			TTDC = TTDC<<1;
		}
		TTCD = Led;
	}
	
	Led  =  0x00;
}

void display_number_define(unsigned int number)
{
	unsigned char nghin, tram, chuc, dvi;
	
	nghin = number/1000;
	tram = (number%1000)/100;
	chuc = (number%100)/10;
	dvi = number%10;

	Led_7Seg = Number[nghin];
	Control_Led1 = 0;
	delay_ms(2);
	Control_Led1 = 1;
	
	Led_7Seg = Number[tram];
	Control_Led2 = 0;
	delay_ms(2);
	Control_Led2 = 1;
	
	Led_7Seg = Number[chuc];
	Control_Led3 = 0;
	delay_ms(2);
	Control_Led3 = 1;
	
	Led_7Seg = Number[dvi];
	Control_Led4 = 0;
	delay_ms(2);
	Control_Led4 = 1;
}

/*
moi 1s se tang so len 1 lan

ma trong "ham display_number_define" co delay 8 ms

-->thoi gian vong lap i = 1000ms/8ms = 125 lan
*/
void display_number_from_x_to_y(unsigned int x, unsigned int y)
{
	unsigned int i, k;
	
	if(x<y)
	{
		for(k=x; k<=y; k++)
		{
			if(status != 2)
				break;
			
			for(i=0; i<125; i++)
				display_number_define(k);
			
		}
	}
	else if(x>y)
	{
		for(k=x; k>=y; k--)
		{
			for(i=0; i<125; i++)
				display_number_define(k);
			if(status != 2)
				break;
		}
	}
}

void button()
{
	  if(b1 == 0)
			status = 1;
		
		
		if(status == 1)
				sangDon();
		else if(status == 2)
			display_number_from_x_to_y(0, 9);
		else if(status == 0)
			turnOff();
}

void turnOff()
{
	//turn off all led 7 seg
	Led_7Seg = 0xFF;
	
	//turn off all led single
	Led = 0x00;
}

//cau hinh ngat ngoai
void config_EXT()
{
	EX0=1;
	EX1=1;
	
	IT0=1;
	IT1=1;
	
	EA=1;
}

void EX0_ISR() interrupt 0
{
	status = 2;
}

void EX1_ISR() interrupt 2
{
	status = 0;
}
