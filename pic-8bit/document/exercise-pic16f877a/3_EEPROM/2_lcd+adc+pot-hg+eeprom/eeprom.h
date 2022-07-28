/* 
 * File:   eeprom.h
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 9:17 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif


    #include <xc.h>
    #include <stdint.h>
    void EEPROM_Write(uint8_t, uint8_t);
    void EEPROM_Write_String(uint8_t Address, const char Data[] );
    uint8_t EEPROM_Read(uint8_t);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

