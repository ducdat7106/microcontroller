#include "timer0.h"


/*
Mode 1, timer0 16bit

12MHz/12 = 1MHz = f 

T=1/1MHz = 1us

16bit = 2^16 - 1 = 65535

1    lenh   1us

1000 lenh   1000us

65535 lenh  65535us  --> sau 65535 lenh timer se sinh ngat 1 lan

de timer sinh ngat moi 1ms 1 lan ==> 1000us --> can 1000 lenh

-->65535-1000 + 1 = 64536 = TL0 + TH0
*/
void timer0_init()
{
	#if mode == 1 //1000us = 1ms will set flag interrupt 
	
		// Chon mode 1 cho T0
		TMOD &= 0xF0;	// Xoa cac bit dieu khien thanh ghi TMOD cua T0
		TMOD |= 0x01;	// Cho mode 1 cho timer0
		
		TL0 = 0x18; //64536 = FC18 = 65535-1000+1 --> 1ms sinh ngat 1 lan
		TH0 = 0xFC;
		
		ET0 = 1;         // Enable Timer0 interrupts
		EA  = 1;         // Global interrupt enable
		
		TF0 = 0;				 //clear flag interrupt
		
		TR0 = 1;         // Start Timer 0
	
	#elif mode == 2 //250us auto reloading time
	
		// Chon mode 2cho T0
		TMOD &= 0xF0;	// Xoa cac bit dieu khien thanh ghi TMOD cua T0	
		TMOD |= 0x02; // Cho mode 1 cho timer0
		
		TH0 = 0x05;      // 250 usec reloading time
		TL0 = 0x05;      // First time value
		
		ET0 = 1;         // Enable Timer0 interrupts
		EA  = 1;         // Global interrupt enable
		
		TF0 = 0;				 //clear flag interrupt
		
		TR0 = 1;         // Start Timer 0
		
	#endif
	
}

void timer0_ISR(void) interrupt 1		
{
	#if mode == 1		//// It is called after every 1 ms
		//do thing
		do_thing_in_interrupt();
		
		//end do thing
	
		TF0 = 0;  // Clear the interrupt flag
	
		TL0 = 0x18;//unload value for timer0
		TH0 = 0xFC;
		
	#elif mode == 2 //// It is called after every 250 us
		//do thing
		xung_test = !xung_test;
	
	
		//end do thing
	
		TF0 = 0;  // Clear the interrupt flag
	
		//no unload value for timer0 so auto unload value
	
	#endif
}

