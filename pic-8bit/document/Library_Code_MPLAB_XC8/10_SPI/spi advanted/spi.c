#include "spi.h"

//SPI Initialization Function

void SPI_Init(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5 = 0;
    if(sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    
    SSPCON = sType | sClockIdle;
}

/*
SPI Wait Function

Following function will wait till data reception to complete.
*/
static void SPI_ReceiveWait()
{
    while ( !SSPSTATbits.BF ); // Wait for Data Receive complete
}


/*
SPI Write

Following function will write data to SSPBUF register, for transmitting data.
*/
void SPI_Write(char data)  //Write data to SPI bus
{
    SSPBUF = data;
}


/*
SPI Data Ready

Following function can be used to check whether any data is available to read.
*/
unsigned SPI_DataReady() //Check whether the data is ready to read
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}


/*
SPI Read

Following function is used to read data.

Note : This function reads only already received / receiving data.
If you want to read it from slave, you should read it after writing a dummy data to 
that slave.
*/
char SPI_Read() //REad the received data
{
    SPI_ReceiveWait();        // wait until the all bits receive
    return(SSPBUF); // read the received data from the buffer
}
