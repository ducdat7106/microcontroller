#include "timer0.h"

void timer0_init()
{
	#if mode == 1 //1000us = 1ms will set flag interrupt 
	
		// Chon mode 1 cho T0
		TMOD &= 0xF0;	// Xoa cac bit dieu khien thanh ghi TMOD cua T0
		TMOD |= 0x01;	// Cho mode 1 cho timer0
		
		TL0 = 0x18; //64536 = FC18 = 65535-1000+1 --> 1ms sinh ngat 1 lan
		TH0 = 0xFC; //TL = 18, TH = FC;
		
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
		
		//TR0 = 1;         // Start Timer 0
		
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
		do_thing_in_interrupt();
		//end do thing
	
		TF0 = 0;  // Clear the interrupt flag
	
		//no unload value for timer0 so auto unload value
	
	#endif
}