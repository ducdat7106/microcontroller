/*
 *	LCD interface example
 *	Uses routines from delay.c
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 bit mode, with
 *	the hardware connected as follows (the standard 14 pin 
 *	LCD connector is used):
 *	
 *	PORTD bits 0-3 are connected to the LCD data bits 4-7 (high nibble)
 *	PORTA bit 3 is connected to the LCD RS input (register select)
 *	PORTA bit 1 is connected to the LCD EN bit (enable)
 *	
 *	To use these routines, set up the port I/O (TRISA, TRISD) then
 *	call lcd_init(), then other routines as required.
 *	
 */

#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 4MHz system frequency is assumed
 #define _XTAL_FREQ 4000000
#endif

#include	<htc.h>
#include	"lcd.h"

#define	LCD_RS RA3
#define	LCD_RW RA2
#define LCD_EN RA1

#define LCD_DATA	PORTD

#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

/* write a byte to the LCD in 4 bit mode */

void
lcd_write(unsigned char c)
{
  //  LCD_RS=1;
	__delay_us(100);
	LCD_DATA = ( ( c >> 4 ) & 0x0F );
	LCD_STROBE();
	LCD_DATA = ( c & 0x0F );
	LCD_STROBE();
}

void
lcd_write_Cmd(unsigned char c)
{
    LCD_RS=0;
	__delay_us(100);
	LCD_DATA = ( ( c >> 4 ) & 0x0F );
	LCD_STROBE();
	LCD_DATA = ( c & 0x0F );
	LCD_STROBE();
    __delay_us(100);
    
}
/*
 * 	Clear and home the LCD
 */

void
lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x1);
	__delay_ms(2);
}

/* write a string of chars to the LCD */

void
lcd_puts(const char * s)
{
	LCD_RS = 1;	// write characters
	while(*s)
		lcd_write(*s++);
}

/* write one character to the LCD */

void
lcd_putch(char c)
{
	LCD_RS = 1;	// write characters
	lcd_write( c );
}


/*
 * Go to the specified position
 */

void
lcd_goto(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x80+pos);
}
	
/* initialise the LCD - put into 4 bit mode */
void
lcd_init()
{
	char init_value;

	ADCON1 = 0x06;	// Disable analog pins on PORTA

	init_value = 0x3;
	TRISA=0;
	TRISD=0;
	LCD_RS = 0;
	LCD_EN = 0;
	LCD_RW = 0;
	
	__delay_ms(15);	// wait 15mSec after power applied,
	LCD_DATA	 = init_value;
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = 2;	// Four bit mode
	LCD_STROBE();

	lcd_write(0x28); // Set interface length
	lcd_write(0xC); // Display On, Cursor Off, Cursor Blink Off
	lcd_clear();	// Clear screen
	lcd_write(0x6); // Set entry Mode
   // lcd_write(0xC0); // Set entry Mode
}
