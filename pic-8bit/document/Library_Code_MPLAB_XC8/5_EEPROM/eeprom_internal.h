/* 
 * File:   eeprom.h
 * Author: Nguyen Duc Dat
 * Created 8_2020
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include<stdint.h>
#include<string.h>

void EEPROM_Write_Char(uint8_t Address, uint8_t Data);
void EEPROM_Write_String(uint8_t Address, const char Data[] );
void EEPROM_Write_N_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes);

    
uint8_t EEPROM_Read_Char(uint8_t Address);
void EEPROM_Read_String(unsigned char eeprom_address, unsigned char *destination_address);
void EEPROM_Read_N_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes);

    

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

