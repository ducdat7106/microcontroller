/* 
 * File:   I2C_SLAVE.h
 * Author: Nguyen Duc Dat
 *
 * Created on 9 December, 2021, 4:10 PM
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

#ifdef	__cplusplus
extern "C" {
#endif
void I2C_Slave_Init(unsigned char Address);    
    
/*Setup I2C (For Slave Mode + Assign It An Address ), Enable Interrupts*/
void I2C_Slave_Init(unsigned char Address)
{
  //---[ Configures The I2C In Slave Mode]---
  SSPADD = Address; // Set The I2C Slave Device Address
  SSPSTAT = 0x80;    //  set standard slew rate
  SSPCON = 0x36;    //As a slave device//// Select & Enable I2C (Slave Mode)
  SSPCON2 = 0x01;   // Enable Clock Stretching
  TRISC3 = 1;     // Set RC3/SDA pins as a input pin
  TRISC4 = 1;     // Set RC4/SCL pins as a input pin
  
  GIE = 1;          //Global interrupt enable
  PEIE = 1;         //Peripheral interrupt enable
  SSPIF = 0;        //Clear interrupt flag
  SSPIE = 1;         // Enable  PICI2C module interrrupt //Synchronous serial port interrupt enable
}

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

