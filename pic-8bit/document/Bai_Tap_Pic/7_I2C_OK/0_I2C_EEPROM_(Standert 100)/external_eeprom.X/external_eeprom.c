#include "external_eeprom.h"

//I2C_BaudRate = 100 (KHz) is ok
void EEPROM_Init(unsigned char I2C_BaudRate)
{
    I2C_Master_Init(I2C_BaudRate);
}

//=========================================================
//=======================EEPROM Write Operations===========
//=======================================================


//=========Single-Byte Write=============
// EEPROM Write Byte
void EEPROM_Write(unsigned char add, unsigned char data)
{
  I2C_Master_Start();
 
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
 
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_Write(data);
  I2C_Master_Stop();
  __delay_ms(20);
}

//=============Page Write===================
// EEPROM Write Page
void EEPROM_Write_Page(unsigned char add, unsigned char* data, unsigned char len)
{
  I2C_Master_Start();
 
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
 
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  for(unsigned int i=0; i<len; i++)
    I2C_Master_Write(data[i]);
  
  I2C_Master_Stop();
}

//=======================================================
//==========================EEPROM Read Operations==========
//=========================================================

//=========Random Byte Read==================

//---[ Byte Read ]---
unsigned char EEPROM_Read(unsigned char add)
{
  unsigned char Data;
  I2C_Master_Start();
 
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
 
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_RepeatedStart();
 
  I2C_Master_Write(EEPROM_Address_R);
  Data = I2C_Master_Read();
  I2C_Master_NACK();
  I2C_Master_Stop();
 
  return Data;
}

//=================Sequential (Page) Read============

//---[ Sequential Read ]---
void EEPROM_Read_Page(unsigned char add, unsigned char* data, unsigned int len)
{
  I2C_Master_Start();
 
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
 
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_RepeatedStart();
  I2C_Master_Write(EEPROM_Address_R);
  for(unsigned int i=0; i<len; i++)
  {
    data[i] = I2C_Master_Read();
    I2C_Master_ACK();
  }
  I2C_Master_Stop();
}

