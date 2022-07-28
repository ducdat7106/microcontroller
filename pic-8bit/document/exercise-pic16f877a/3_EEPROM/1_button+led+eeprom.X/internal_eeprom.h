/* 
 * File:   internal_eeprom.h
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 3:25 AM
 */

#ifndef INTERNAL_EEPROM_H
#define	INTERNAL_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
/******************************************************************************/
    
#include <xc.h>
#include <stdint.h>

void EEPROM_Write(uint8_t, uint8_t);
uint8_t EEPROM_Read(uint8_t);
    
    
/********************************************************************************/
#ifdef	__cplusplus
}
#endif

#endif	/* INTERNAL_EEPROM_H */

