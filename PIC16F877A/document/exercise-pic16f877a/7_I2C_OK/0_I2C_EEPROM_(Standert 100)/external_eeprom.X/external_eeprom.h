/* 
 * File:   ex_eeprom.h
 * Author: Dat Nguyen
 *
 * Created on 27 November, 2021, 7:20 AM
 */

#ifndef EX_EEPROM_H
#define	EX_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include "i2c.h"
//#define _XTAL_FREQ 16000000

#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0


//---[ EEPROM Routines ]---
void EEPROM_Init(unsigned char I2C_BaudRate);

void EEPROM_Write(unsigned char add, unsigned char data);
void EEPROM_Write_Page(unsigned char add, unsigned char* data, unsigned char len);

unsigned char EEPROM_Read(unsigned char add);
void EEPROM_Read_Page(unsigned char add, unsigned char* data, unsigned int len);



#ifdef	__cplusplus
}
#endif

#endif	/* EX_EEPROM_H */

