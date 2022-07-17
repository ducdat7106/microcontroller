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
char UART_Init( unsigned long uart_baudRate );

void UART_Write_Char(char data);
char UART_TX_Empty();
void UART_Write_String(char *text);

char UART_Data_Ready();
char UART_Read_Char();
void UART_Read_String(char *Output, unsigned int length);

//--------------------------------


#ifdef	__cplusplus
}
#endif

#endif	/* UART_MASTER_H */

