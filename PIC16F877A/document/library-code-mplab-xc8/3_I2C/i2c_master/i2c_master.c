#include"i2c_master.h"

/*
	Setup I2C (For Master Mode)
*/
void I2C_Master_Init(const unsigned long I2C_BaudRate)
{
	SDA_DIR = 1;// Make SDA and SCK pins input
	SCK_DIR = 1;
		
	SSPADD = (unsigned char)( _XTAL_FREQ/(4*I2C_BaudRate) ) - 1;// SSPADD  = ((_XTAL_FREQ/4)/I2C_SPEED) - 1;
	SSPCON = 0x28;// Slew Rate control is disabled
	//SSPCON2 = 0x00;
	SSPSTAT = 0x80;    // Slew Rate control is disabled
	//SSPSTAT = 0x00;	
}


/*
 The I2C_Wait() function which makes your master MCU sure that 
 the previous state has reached completion successfully and the bus is on IDLE,
  so it can proceed to the desired command.
*/
void I2C_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}



/*
Initiate An I2C Start Condition
*/
void I2C_Start()
{
	//---[ Initiate I2C Start Condition Sequence ]---
	I2C_Wait();
	SEN = 1;
}



//Initiate An I2C Restart Condition		Repeated Start
void I2C_Restart()
{
	//---[ Initiate I2C Restart Condition Sequence ]---
	I2C_Wait();
	RSEN = 1;
}



//Initiate An I2C Stop Condition
void I2C_Stop()
{
	//---[ Initiate I2C Stop Condition Sequence ]---
	I2C_Wait();
	PEN = 1;
}



void I2C_ACK(void)
{
	/*
	Send ACK Signal (For Master Receiver Mode Only)
	*/
	ACKDT = 0; // 0 -> ACK
	I2C_Wait();
	ACKEN = 1; // Send ACK
}


void I2C_NACK(void)
{
	//Send NACK Signal (For Master Receiver Mode Only)
	ACKDT = 1; // 1 -> NACK
	I2C_Wait();
	ACKEN = 1; // Send NACK
}


//Send Byte Via I2C Bus, And Return The ACK/NACK From The Slave
unsigned char I2C_Write_Char(unsigned char Data)
{
  //---[ Send Byte, Return The ACK/NACK ]---
  I2C_Wait();
  SSPBUF = Data;
  while(!SSPIF); // Wait Until Completion
  SSPIF = 0;
  return ACKSTAT;
}



//if ACK  -->char  ACK = 0
//if NACK -->char  ACK = 1
//Receive And Return A Byte From The I2C Bus
unsigned char I2C_Read_Char(char ACK)
{
    //---[ Receive & Return A Byte ]---
    uint8_t _data;
    I2C_Wait();
    RCEN = 1;        // Enable & Start Reception
    while(!SSPIF); // Wait Until Completion
  	SSPIF = 0; // Clear The Interrupt Flag Bit
    I2C_Wait();
    _data = SSPBUF;   
    I2C_Wait();
    if(ACK==0)
       I2C_ACK();
    else
       I2C_NACK();
    
    return _data;	// Return The Received Byte
}






void Wait_Mssp()
{
    while(!SSPIF);	// Wait for it to complete
    SSPIF=0;		// Clear the flag bit
}

void I2C_Start_1()
{
    SEN=1;// Send start bit
    Wait_Mssp();
}

void I2C_Restart_1(void)
{
    RSEN=1;// Send Restart bit
    Wait_Mssp();
}

void I2C_Stop_1(void)
{
    PEN=1;// Send stop bit
    Wait_Mssp();
}

void I2C_ACK_1(void)
{
    ACKDT=0;	// 0 means ACK
    ACKEN=1;	// Send ACKDT value
    Wait_Mssp();
}


void I2C_NACK_1(void)
{
    ACKDT=1;	// 1 means NACK
    ACKEN=1;	// Send ACKDT value
    Wait_Mssp();
}


//I2C_Write_Byte transfers one byte
void I2C_Send_1(unsigned char data)
{
L1: SSPBUF=data;	// Send Byte value
    Wait_Mssp();
    while(ACKSTAT)
	{
		I2C_Restart_1();
		goto L1;
	}
	
	//return ACKSTAT;    // Return ACK/NACK from slave
}


//I2C_Read_Byte reads one byte
unsigned char I2C_Read_1(void)
{
    RCEN=1;	// Enable reception of 8 bits
    Wait_Mssp();
    return SSPBUF;	// Return received byte
}  


void I2C_Send_Byte(unsigned char addr,unsigned char *count)
{
    I2C_Start_1();
   	I2C_Send_1(write_cmd);
    I2C_Send_1(addr>>8);
    I2C_Send_1(addr);
    while(*count) {
        I2C_Send_1(*count++);
    }
    I2C_Stop_1();
}


unsigned char I2C_Read_Byte(unsigned char addr)
{
    unsigned char rec;
L:  I2C_Restart();
    SSPBUF=write_cmd;
    Wait_Mssp();
    while(ACKSTAT){goto L;}
    I2C_Send_1((addr>>8);
    I2C_Send_1((addr);
    IWC_Restart_1();
    I2C_Send_1((read_cmd);
    rec=I2C_Read_1(();
    I2C_NACK_1();
    I2C_STOP_1();
    return rec;
}



void I2C_Write_String(unsigned char addr,unsigned char *count)
{
    I2C_Start();
    I2C_Send_1(write_cmd);
    I2C_Send_1(addr>>8);
    I2C_Send_1(addr);
    while(*count) 
    {
        I2C_Send_1(*count++);
    }
    I2C_Stop();
}


unsigned char I2C_Read_String(unsigned char addr)
{
    unsigned char rec;
L:  I2C_Restart_1();
    SSPBUF=write_cmd;
    I2C_Wait();
    while(ACKSTAT)
    {
        goto L;
    }
    I2C_Send_1(addr>>8);
    I2C_Send_1(addr);
    I2C_Restart();
    I2C_Send_1(read_cmd);
    rec = I2C_Read_1();
    I2C_NACK_1();
    I2C_Stop_1();
    return rec;
}




