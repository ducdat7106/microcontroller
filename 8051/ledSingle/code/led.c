#include <REG52.H>

#define Led_Single_Cathode_Mass  P0
#define Led_Single_Anode_Power  P1

#define Led_7Seg_Cathode_Mass P2
#define Led_7Seg_Anode_Power  P3

unsigned char MA7D_Anode_Power[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char MA7D_Cathode_Mass[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void Delay_ms(unsigned int time);
void config();

void blinkLedCathode();
void blinkLedAnode();

void displayLed_7SEG();

int main()
{
		config();
	
    while (1)
    {
				//hien thi 0 ->9
        displayLed_7SEG();
				
				//nhap nhay 1 lan
				blinkLedCathode();
				
			 //nhap nhay 1 lan
				blinkLedAnode();
			
    }
}

void Delay_ms(unsigned int time)
{
    unsigned char j;
    while (time--)
    {
        for (j = 0; j < 123; j++);        
    }
}

void config()
{
	//turn off all led
	Led_Single_Cathode_Mass = 0x00;
	Led_Single_Anode_Power = 0xFF;
	
	Led_7Seg_Cathode_Mass = 0x00;
	Led_7Seg_Anode_Power = 0xFF;
}

void blinkLedCathode()
{
	Led_Single_Cathode_Mass = 0x00;//all led turn off
	Delay_ms(1000);
	Led_Single_Cathode_Mass = 0xFF;//all led turn on
	Delay_ms(1000);	
	
	Led_Single_Cathode_Mass = 0x00;
}

void blinkLedAnode()
{
	Led_Single_Anode_Power = 0xFF;//all led turn off
	Delay_ms(1000);
	Led_Single_Anode_Power = 0x00;//turn on
	Delay_ms(1000);	
	
	Led_Single_Anode_Power = 0xFF;
}

void displayLed_7SEG()
{
	int number;
	
	for(number=0; number<10; number++)
	{
		Led_7Seg_Cathode_Mass = MA7D_Cathode_Mass[number];
		Led_7Seg_Anode_Power = MA7D_Anode_Power[number];
		Delay_ms(1000);
	}
	
	Led_7Seg_Cathode_Mass = 0x00;
	Led_7Seg_Anode_Power = 0xFF;
}
	
	
	
	
	

	