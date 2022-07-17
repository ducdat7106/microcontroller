#include "i2c.h"

//Initialize I2C Module as Master
void I2C_Master_Init(unsigned char I2C_BaudRate)
{
  SSPCON = 0b00101000;            //SSP Module as Master
  SSPCON2 = 0;
  SSPADD = (unsigned char)(_XTAL_FREQ/(4000*I2C_BaudRate))-1; //Setting Clock Speed        //4*I2C_BaudRate*10^3
  SSPSTAT = 0;
  TRISC3 = 1;                   //Setting as input as given in datasheet
  TRISC4 = 1;                   //Setting as input as given in datasheet
}

//For Waiting
void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
}

//Start Condition
void I2C_Master_Start()
{
  I2C_Master_Wait();    
  SEN = 1;             //Initiate start condition
}

//Repeated Start
void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  RSEN = 1;           //Initiate repeated start condition
}

//Stop Condition
void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;           //Initiate stop condition
}


void I2C_Master_ACK(void)
{
  ACKDT = 0; // 0 -> ACK  //Acknowledge Data bit 
  I2C_Master_Wait();
  ACKEN = 1; // Send ACK    // Acknowledge Sequence Enable bit
}
 
void I2C_Master_NACK(void)
{
  ACKDT = 1; // 1 -> NACK
  I2C_Master_Wait();
  ACKEN = 1; // Send NACK
}

unsigned char I2C_Master_Write(unsigned char data)
{
  I2C_Master_Wait();
  SSPBUF = data;
  while(!SSPIF); // Wait Until Completion
  SSPIF = 0;
  return ACKSTAT;
}
 
//Reads a byte
unsigned char I2C_Master_Read(void)
{
  //---[ Receive & Return A Byte ]---
  I2C_Master_Wait();
  RCEN = 1; // Enable & Start Reception
  while(!SSPIF); // Wait Until Completion
  SSPIF = 0; // Clear The Interrupt Flag Bit
  I2C_Master_Wait();
  return SSPBUF; // Return The Received Byte
}



