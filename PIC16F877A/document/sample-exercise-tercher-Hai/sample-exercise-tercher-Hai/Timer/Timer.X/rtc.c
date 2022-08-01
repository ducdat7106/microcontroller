
/**
 * Simple Real time clock example by Garth Klee.
 * If run on PICDEM2+, time will be displayed
 * on LCD and will incorporate LED pendulum.
 * Has been written to run on PIC16F87x/A
 */

#include <htc.h>
#include <stdio.h>
#include "lcd.h"
#include "rtc.h"

__CONFIG(XT & WDTDIS & LVPDIS & DEBUGEN);

volatile near unsigned char tickCounter;
volatile near unsigned char newSecond;

near unsigned char hours;
near unsigned char minutes;
near unsigned char seconds;
near bit ampm;

// Pendulum pattern to display on LEDs (RB0:3)
const unsigned char pattern[] = {1,2,4,8,4,2};

void init(void){
	/***** Common Code ****
	 *  Timer 2 interrupt enabled.
	 */
	PIE1	= 0b00000010;
	/*
	 *  Peripheral interrupts enabled
	 *  Global interrupt disabled during initialization
	 */
	INTCON	= 0b01000000;
	
	/***** Timer 2 Code ****
	 *  Prescale ratio set at 1:16
	 *  Timer2 module activated
	 *  Postscale ratio set at 1:10
	 */
	T2CON	= 0b01001110;
	/*
	 *  Period register set to 0xF9
	 */
	PR2	= 0b11111001;

#if PENDULUM == ON
	TRISB = 0;
#endif
#if ((TICKING == ON)||(ALARM == ON))
	TRISC2=0;
#endif
	
	ei();	// Global interrupts enabled
}

void main(void){
	init();
#if SCREEN == ON
	lcd_init();
#endif

	newSecond = tickCounter = 0;

	// Initialise the current time
	hours = START_H;
	minutes = START_M;
	seconds = START_S;
	ampm = START_AP;

	// Measure time
	while(1){
		if(newSecond){
			// A second has accumulated, count it
			newSecond--;
			if(++seconds > 59){
				seconds=0;
				if(++minutes > 59){
					minutes = 0;
					hours++;
					if(hours == 12)
						ampm^=1;
					if(hours>12)
						hours=1;
				}
			}

#if SCREEN == ON
			// print time on LCD screen
			lcd_goto(0);
			lcd_puts("Time=");
			// Print hours
			if(hours/10)
				lcd_putch('1');
			else
				lcd_putch(' ');
			lcd_putch((hours%10)+'0');
			lcd_putch(':');
			// print minutes
			lcd_putch((minutes/10)+'0');
			lcd_putch((minutes%10)+'0');
			lcd_putch(':');
			// print seconds
			lcd_putch((seconds/10)+'0');
			lcd_putch((seconds%10)+'0');
			if(ampm)
				lcd_putch('P');
			else
				lcd_putch('A');
			lcd_putch('M');
#endif

#if PENDULUM == ON
			// Rotate LED pattern every second
			PORTB=(pattern[seconds%sizeof(pattern)]);
#endif
#if TICKING == ON
			RC2^=1;	// tick effect
#endif

		}
#if ALARM == ON
		// If time matches alarm setting, toggle RC2
		if((hours == ALARM_H) &&
				(minutes == ALARM_M) &&
				(ampm == ALARM_AP)&&
				(seconds < ALARM_LENGTH)){
			unsigned int tone;
			RC2 ^= 1;	// generate buzz
			tone=TONE2;
			if(seconds&1)
				tone=TONE1;
			while(tone--)continue;	// tone generation
			RC2 ^= 1;	// generate buzz
		}
#endif
	}
}

void interrupt isr(void){
		/***** Timer 2 Code *****/
	if((TMR2IE)&&(TMR2IF)){
		// Interrupt period is 40 mSec, 25 interrupts = 1 Sec
		if(++tickCounter == 25){
			tickCounter=0;
			newSecond++;	// Notify a second has accumulated
		}
		TMR2IF=0;	// clear event flag
	}
}
