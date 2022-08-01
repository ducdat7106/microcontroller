#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
   

/*                    LCD Commands
  Hex Code	Command to LCD Instruction Register
  
		0F	LCD ON, cursor ON
		01	Clear display screen
		02	Return home
		04	Decrement cursor (shift cursor to left)
		06	Increment cursor (shift cursor to right)
		05	Shift display right
		07	Shift display left
		80	Force cursor to beginning of first line
		C0	Force cursor to beginning of second line
		38	2 lines and 5x7 matrix
		83	Cursor line 1 position 3
		3C	Activate second line	
		08	Display OFF, cursor OFF
		0E	Display ON, cursor blinking
		OC	Display ON, cursor OFF
		C1	Jump to second line, position 1
		C2	Jump to second line, position 2 
		C3	Jump to second-line position 3
*/   
    
// Command set for Hitachi 44780U LCD display controller
#define LCD_CLEAR 0x01    		// It clears everythings 
#define LCD_HOME 0x02   		// set the cursor to first line and first row
#define LCD_CURSOR_BACK 0x10	// moves curson one position back
#define LCD_CURSOR_FWD 0x14  	//moves curson one position forward
#define LCD_PAN_LEFT 0x18       // used to scroll text left side to scroll text
#define LCD_PAN_RIGHT 0x1C   	// used to scroll text right side to scroll text
#define LCD_CURSOR_OFF 0x0C 	// stops display curson on screen
#define LCD_CURSOR_ON 0x0E  	// turns on cursor display
#define LCD_CURSOR_BLINK 0x0F 	// curson keeps blinking
#define LCD_CURSOR_LINE2 0xC0   // move curson to scond line or second row


// display controller setup commands from page 46 of Hitachi datasheet
#define FUNCTION_SET 0x28 		// 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE 0x06 		// increment mode
#define DISPLAY_SETUP 0x0C 		// display on, cursor off, blink offd


#define LCD_EN_Delay 500
#define LCD_DATA_PORT_D TRISD	//Data Bus Direction_ huong bus du lieu
#define LCD_RS_D TRISD2
#define LCD_EN_D TRISD3
    
#define RS RD2 //register select line
#define EN RD3 //enable
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
    
void LCD_Init();
void LCD_Clear();
void LCD_Set_Cursor(unsigned char, unsigned char);

void LCD_Write_Char(char);
void LCD_Write_String(char*);

void LCD_Write_Number(unsigned int number);


void LCD_SL();
void LCD_SR();
void LCD_Cmd(unsigned char);
void LCD_Set_Bit(unsigned char);
#ifdef	__cplusplus
}
#endif

#endif

