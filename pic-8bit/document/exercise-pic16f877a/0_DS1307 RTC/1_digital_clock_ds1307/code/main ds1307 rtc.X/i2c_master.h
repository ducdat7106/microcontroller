/* 
 * File:   I2C.h
 * Author: Nguyen Duc Dat
 * Created : 8_2020
 */

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define SDA  PORTCbits.RC4      // Data pin for i2c
#define SCK  PORTCbits.RC3       // Clock pin for i2c
#define SDA_DIR  TRISCbits.TRISC4     // Data pin direction
#define SCK_DIR  TRISCbits.TRISC3      // Clock pin direction
    
#define I2C_SPEED_FACTOR	1	// Low value means low i2c frequency	
#define I2C_SPEED  100        // kbps
#define Crystal_Value		12  // MHz
#define HalfBitDelay 		(500*Crystal_Value)/(12*I2C_SPEED_FACTOR)
    
// Define macros
#define Set_SDA_Low	  PORTCbits.RC4=0
#define Set_SDA_High  PORTCbits.RC4=1
#define Set_SCK_Low	  PORTCbits.RC3=0
#define Set_SCK_High  PORTCbits.RC3=1

#define write_cmd 0xA0
#define read_cmd 0xA1

void I2C_Master_Init(const unsigned long I2C_BaudRat);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);

unsigned char I2C_Read_Char(char ACK);
unsigned char I2C_Write_Char(unsigned char Data);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */


