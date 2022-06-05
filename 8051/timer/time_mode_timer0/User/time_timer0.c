#include "time_timer0.h"

/*
crytal =12 MHz
qua bo chia truoc /12--> f = 12/12=1Mhz

chu ky lenh = 1us

-->de chay 1ms can 1000 lenh

timer0 16bit = 65536
-->65536-1000  =  64536

-->co ngat se bat

dec  -  64536
hex  -  FC18   ---> TL0 = 18
               ---> TH0 = FC
*/
void initTimer0(int mode)
{
	//mode 1, timer0 16bit
	if(mode == 1)
	{
		// Chon mode cho T0
		TMOD &= 0xF0;	// Xoa cac bit dieu khien thanh ghi TMOD cua T0
		TMOD |= 0x01;	// Cho mode 1 cho timer0
	}
}

void delay_ms_timer0(unsigned int t)
{
	do{
	 	TL0 = 0x18;
		TH0 = 0xFC;
		TR0 = 1;	// Timer0 bat dau dem
		while(!TF0); //kiem tra co ngat
		TR0 = 0;	// Timer0 ngung dem
		TF0 = 0;

		t--;
	}while(t!=0);
}

/*
//khong toi uu de su dung

void delay_ms_timer0(unsigned int t)
{
		unsigned int cnt;
			
	 	TL0 = 0;
		TH0 = 0;
		TR0 = 1;	// Timer0 bat dau dem
		
		do{
			cnt = TH0;
			cnt <<= 8;
			cnt |= TL0;
		}while(cnt<=1000)
			
		TR0 = 0;	// Timer0 ngung dem

		t--;
	}while(t!=0);
}
*/