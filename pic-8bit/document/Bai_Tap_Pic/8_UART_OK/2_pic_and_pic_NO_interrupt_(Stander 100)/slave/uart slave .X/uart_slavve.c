#include"uart salve.h"

//Initializing UART
char UART_Init( unsigned long uart_baudRate )
{
    unsigned int x;
    x = (_XTAL_FREQ - uart_baudRate*64)/(uart_baudRate*64); // Low Baud Rate
    if(x>255)  
    {
        x = (_XTAL_FREQ - uart_baudRate*16)/(uart_baudRate*16); // High Baud Rate
        BRGH = 1;
    }
    else 
        BRGH = 0;

    
    if (x<=255)//x<256
    {
        SPBRG = x;  //Writing SPBRG Register

        //--[ Enable The Ascynchronous Serial Port ]--
        SYNC = 0;//Setting Asynchronous Mode, ie UART
        SPEN = 1;//Enables Serial Port

        //--[ Set The RX-TX Pins to be in UART mode (not io) ]--
        TRISC6 = 1;   // As stated in the datasheet
        TRISC7 = 1;   // As stated in the datasheet
        TXEN = 1;     // Enable UART Transmission
        CREN = 1;//Enables Continuous Reception
        return 1; //Returns 1 to indicate Successful Completion
    }
    return 0;//Returns 0 to indicate UART initialization failed
}
 /////////////////////////////////////////////////////////////
/////////////////Sending Data Through UART//////////////////////
////////////////////////////////////////////////////////////////

//Writing a Character
void UART_Write_Char(char data)
{
  while(!TRMT);
  TXREG = data;
}

//Checking Transmit Register
char UART_TX_Empty()
{
    return TRMT;
}

//Writing Text
void UART_Write_String(char *text)
{
    for(int i=0;text[i]!='\0';i++)
	  UART_Write_Char(text[i]);
}

//////////////////////////////////////////////////////////////////
//////////////////Receiving Data Through UART///////////////////
////////////////////////////////////////////////////////////////////////


/*
//=====  Data Received or Not  =======
*
The following function can be used to check whether the data is ready to read from the Receive Register. 
It uses the flag bit RCIF which will be set when the data reception is completed. 
*/
char UART_Data_Ready()
{
    return RCIF;
}

/*
//Reading a Character
 * 
The following function wait till the reception is complete and reads 8 bit data from the Receive Register.
 */
char UART_Read_Char()
{
  while(!RCIF);
  return RCREG;
}

/*
//Reading Text
 * 
The following function can be used to read a desired length of text or sequence of characters continuously.
 */
void UART_Read_String(char *Output, unsigned int length)
{
	unsigned int i;
	for(int i=0;i<length;i++)
		Output[i] = UART_Read_Char();
}



