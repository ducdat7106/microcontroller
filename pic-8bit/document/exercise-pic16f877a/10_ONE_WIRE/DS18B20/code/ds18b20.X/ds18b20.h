/* 
 * File:   ds18b20.h
 * Author: Nguyen Duc Dat
 *
 * Created on 25 December, 2021, 8:29 AM
 * 
 * https://simple-circuit.com/mplab-xc8-ds18b20-pic-microcontroller/
 * 
 */

#ifndef DS18B20_H
#define	DS18B20_H

#ifdef	__cplusplus
extern "C" {
#endif

/***********************Start Code  DS18B20****************************/
#include<xc.h>
#include<stdint.h>
    
// DS18B20 data pin is connected to pin RB1
#define DS18B20_PIN      RD7
#define DS18B20_PIN_Dir  TRISD7
    

__bit ds18b20_start();

void ds18b20_write_bit(uint8_t value);
void ds18b20_write_byte(uint8_t value);

__bit ds18b20_read_bit(void);
uint8_t ds18b20_read_byte(void);

__bit ds18b20_read(uint16_t *raw_temp_value);
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* DS18B20_H */

