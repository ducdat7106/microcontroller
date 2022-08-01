#include<xc.h>

char UART_Init(const long int baudrate);
char UART_TX_Empty();
char UART_Data_Ready();
char UART_Read();
void UART_Read_Text(char *Output, unsigned int length);
void UART_Write(char data);
void UART_Write_Text(char *text);

/////
////
//Initializing UART
////
////

//baudrate = 9600  is OK

//return 1 is ok
char UART_Init(const long int baudrate)
{
	unsigned int x;
	
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);//SPBRG for Low Baud Rate
	if(x>255)									//If High Baud Rage Required
	{
		x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);//SPBRG for High Baud Rate
		BRGH = 1;									 //Setting High Baud Rate
	}
	
	if(x<255)
	{
	  SPBRG = x;//Writing SPBRG Register
	
	// Enable The Ascynchronous Serial Port
  	SYNC = 0; //Setting Asynchronous Mode, ie UART
  	SPEN = 1; //Enables Serial Port
  	
  	// Set The RX-TX Pins to be in UART mode (not io)
  	TRISC7 = 1;// RX Pin set as input		// As stated in the datasheet
 	TRISC6 = 1;// As stated in the datasheet
 	/*
	 giao tiep giua 2 pic -->TRISC6=1;
	 giao tiep giua pic va may tinh --->TRISC6=0;// TX Pin set as output
	 */
	 
 	//--[ Enable UART Receiving Interrupts ]--
	RCIE = 1; // UART Receving Interrupt Enable Bit
	PEIE = 1; // Peripherals Interrupt Enable Bit
	GIE = 1; // Global Interrupt Enable Bit
	//------------------------------------------
	
 	CREN = 1;//enable reception	-----// Enable Data Continous Reception-
  	TXEN = 1; //Enables Transmission
 	
 	//**Select 8-bit mode**//  
    TX9   = 0;    // 8-bit reception selected
    RX9   = 0;    // 8-bit reception mode selected
    //__8-bit mode selected__//     
    
 	return 1; //Returns 1 to indicate Successful Completion
	}
	
	return 0;//Returns 0 to indicate UART initialization failed
}

///
///
//Sending Data Through UART
///
///


/*Checking Transmit Register*/
char UART_TX_Empty()
{
  return TRMT;
}
/*Writing a Character*/
void UART_Write(char data)// UART_send_char
{
  while(!TRMT);// hold the program till TX buffer is free
  TXREG = data;//Load the transmitter buffer with the received value
}
/*Writing Text*/
void UART_Write_Text(char *text)//UART_send_string
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write(text[i]);
}

////
////
//Receiving Data Through UART
////
////

/*Data Received or Not*/
/*
char UART_Data_Ready()
{
   return RCIF;
}
*/
/*Reading a Character*/
/*
char UART_Read()
{
 
  while(!RCIF);// Wait Untill a Data Frame is Received
  return RCREG;
}
*/

//**Function to get one byte of date from UART**//
char UART_Read()//UART_get_char()   
{
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    
    while(!RCIF);  // hold the program till RX buffer is free
    
    return RCREG; //receive the value and send it to main function
}

/*Reading Text*/
void UART_Read_Text(char *Output, unsigned int length)
{
	int i;
	for(i=0;i<length;i++)
		Output[i] = UART_Read();
}

