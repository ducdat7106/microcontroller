/* 
 * File:   i2c.h
 * Author: DAT PC
 *
 * Created on 13 February, 2022, 3:44 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

//#define _XTAL_FREQ 16000000
    
//---[ I2C Routines ]---
void I2C_Master_Init(unsigned char I2C_BaudRate);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_Master_ACK();
void I2C_Master_NACK();
unsigned char I2C_Master_Write(unsigned char);
unsigned char I2C_Master_Read(void);



#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

