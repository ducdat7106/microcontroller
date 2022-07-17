/*
File : EEPROM.h
Time : 8-2020
Author : Nguyen Duc Dat
*/

//#define _XTAL_FREQ 16000000
//@definr I2C_BaudRate 100000

#include <xc.h>

#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0

//---[ EEPROM Routines ]---
void EEPROM_I2C_Init( const unsigned long I2C_BaudRate );

void EEPROM_Write_Char(unsigned int add, unsigned char data);
void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len);

unsigned char EEPROM_Read_Char(unsigned int add);
void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len


