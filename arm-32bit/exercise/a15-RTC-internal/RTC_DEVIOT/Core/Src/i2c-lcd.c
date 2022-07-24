#include "i2c-lcd.h"

void LCD_Send_Cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);		// select only upper nibble
	data_l = ((cmd<<4)&0xf0);	// select only lower nibble
	data_t[0] = data_u|0x0C;  	//en=1, rs=0
	data_t[1] = data_u|0x08;  	//en=0, rs=0
	data_t[2] = data_l|0x0C;  	//en=1, rs=0
	data_t[3] = data_l|0x08;  	//en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void LCD_Init (void)
{
	// 4 bit initialisation
	LCD_Send_Cmd (0x33); /* set 4-bits interface */
	LCD_Send_Cmd (0x32);
	HAL_Delay(50);
	LCD_Send_Cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	LCD_Send_Cmd (0x01); /* clear display */
	HAL_Delay(50);
	LCD_Send_Cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	LCD_Send_Cmd (0x0c); /* set display to on */	
	HAL_Delay(50);
	LCD_Send_Cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	LCD_Send_Cmd (0x80);
}

#ifdef LCD16
/*
row    =  1, 2
column =  1, 2, 3, 4.....15, 16
*/
void LCD_Set_Cursor (int row, int col)
{
	uint8_t pos_Addr;

	if(row == 1) 
	{
		pos_Addr = 0x80 + row - 1 + col-1;
	}
	else if(row == 2)
	{
		pos_Addr = 0x80 | (0x40 + col-1);
	}
	else if(row == 3)
	{
		pos_Addr = 0x80 | (0x10 + col-1);
	}
	else
	{
		pos_Addr = 0x80 | (0x50 + col-1);
	}

	LCD_Send_Cmd (pos_Addr);
}
#endif


#ifdef  LCD20
/*
row    =  1, 2, 3, 4
column =  1, 2, 3, 4.....19, 20
*/
void LCD_Set_Cursor (int row, int col)
{
	uint8_t pos_Addr;

	if(row == 1)
	{
		pos_Addr = 0x80 + row - 1 + col-1;
	}
	else if(row == 2)
	{
		pos_Addr = 0x80 | (0x40 + col-1);
	}
	else if(row == 3)
	{
		pos_Addr = 0x80 | (0x14 + col-1);
	}
	else
	{
		pos_Addr = 0x80 | (0x54 + col-1);
	}

	LCD_Send_Cmd (pos_Addr);
}
#endif

void LCD_Write_Char (char data)	//void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);		// select only upper nibble
	data_l = ((data<<4)&0xf0);	// select only lower nibble
	data_t[0] = data_u|0x0D;  	//en=1, rs=0
	data_t[1] = data_u|0x09;  	//en=0, rs=0
	data_t[2] = data_l|0x0D;  	//en=1, rs=0
	data_t[3] = data_l|0x09;  	//en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void LCD_Write_String (char *str)
{
	while (*str) LCD_Write_Char (*str++);
}

void LCD_Clear (void)
{
	
	LCD_Send_Cmd (0x01); //clear display
}


