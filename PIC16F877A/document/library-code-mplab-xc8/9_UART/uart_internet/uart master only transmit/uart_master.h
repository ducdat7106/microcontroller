/* 
 * File:   uart_master.h
 * Author: Nguyen Duc Dat
 *
 * Created on 12 December, 2021, 2:39 PM
 */

#ifndef UART_MASTER_H
#define	UART_MASTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include<stdint.h>
    
// Functions Declarations
void UART_TX_Init(unsigned long uart_baudRate);
void UART_Write_Char(char);
void UART_Write_String(char *);

char UART_TX_Empty();
//--------------------------------


#ifdef	__cplusplus
}
#endif

#endif	/* UART_MASTER_H */

