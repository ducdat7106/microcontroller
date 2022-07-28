/* 
 * File:   uart salve.h
 * Author: Nguyen Duc Dat
 *
 * Created on 12 December, 2021, 3:05 PM
 */

#ifndef UART_SALVE_H
#define	UART_SALVE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include<stdint.h>
    
void UART_RX_Init(unsigned long uart_baudRate);
uint8_t UART_Read_Char(void);
void UART_Read_String(uint8_t *Output, uint16_t length);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_SALVE_H */

