#include "I2C_EEPROM.h"
#include "i2c.h"

void I2C_EEPROM_Init( const unsigned long I2C_baudRate )
{
	I2C_Master_Init(I2C_baudRate);
}


//-----[ Write Operations ]-----

void EEPROM_Write_Char(unsigned int add, unsigned char data)
{
	/*
	Single-Byte Write
	
	EEPROM Write Byte
	*/
	I2C_Start();
	// Wait Until EEPROM Is IDLE
	while(I2C_Write_Char(EEPROM_Address_W))
	I2C_RepeatedStart();
		I2C_ACK();
	I2C_Write_Char(add>>8);
	I2C_Write_Char((unsigned char)add);
		I2C_ACK();
	I2C_Write_Char(data);
		I2C_ACK();
	I2C_Stop();
}

void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len)
{
	/*
	Page Write
	EEPROM Write Page
	*/
	I2C_Start();
	// Wait Until EEPROM Is IDLE
	while(I2C_Write(EEPROM_Address_W))
	I2C_RepeatedStart();
		I2C_ACK();
	I2C_Write_Char(add>>8);
	I2C_Write_Char((unsigned char)add);
		I2C_ACK();
	for(unsigned int i=0; i<len; i++)
	{
		I2C_Write_Char(data[i]);
			I2C_ACK();
	}
	I2C_Stop();
}









//-----[ Current Address Read Operations ]-----

unsigned char EEPROM_Read_Char(unsigned int add)
{
	/*
	Random Byte Read
	
	Byte Read
	*/
	unsigned char Data;
	
	I2C_Start();
	
	// Wait Until EEPROM Is IDLE
	while(I2C_Write_Char(EEPROM_Address_W))
	I2C_RepeatedStart();
		I2C_ACK();
	I2C_Write_Char(add>>8);
	I2C_Write_Char((unsigned char)add);
		I2C_ACK();
	I2C_RepeatedStart();
	I2C_Write_Char(EEPROM_Address_R);
		I2C_ACK();
	Data = I2C_Read_Char();
		I2C_NACK();
	I2C_Stop();
	
	return Data;
}

//---[ Sequential Read ]---
void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len)
{
	/*
	Sequential (Page) Read
	*/
	I2C_Start();
	
	// Wait Until EEPROM Is IDLE
	while(I2C_Write_Char(EEPROM_Address_W))
	I2C_RepeatedStart();
	
	I2C_Write_Char(add>>8);
	I2C_Write_Char((unsigned char)add);
	
	I2C_RepeatedStart();
	
	I2C_Write_Char(EEPROM_Address_R);
	
	for(unsigned int i=0; i<len-1; i++)
	{
		data[i] = I2C_Read_Char();
		I2C_ACK();
	}
	data[len-1] = I2C_Read_Char();
		I2C_NACK();
	
	I2C_Stop();
}


//--------------[Random Read]----------------------------------











//-------------------[Sequential Read]---------------------------------------



















