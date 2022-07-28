//https://circuitdigest.com/microcontroller-projects/uart-communication-using-pic16f877a

#include<xc.h>

char UART_TX_AND_RX_Init(unsigned long baudrate);
char UART_TX_Empty();
char UART_Data_Ready();
char UART_Read_Char();
void UART_Read_String(char *Output, unsigned int length);
void UART_Write_Char(char data);
void UART_Write_String(char *text);


//Initializing UART
    //baudrate = 9600  is OK
    //_XTAL_FREQ = 20MHz

    //return 1 is ok
    
    //SPBRG = ( ( _XTAL_FREQ/16 ) / Baud_rate) – 1;
char UART_TX_AND_RX_Init(unsigned long baudrate)
{	

	unsigned int x;
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);//SPBRG for Low Baud Rate
	if(x>255)									//If High Baud Rage Required
	{
		x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);//SPBRG for High Baud Rate
		BRGH = 1;									 //Setting High Baud Rate
	}
	else 
		BRGH = 0;  //setting low speed baud rate
	
	if(x<255)
	{
	  SPBRG = x;//Writing SPBRG Register
	
	// *****Enable The Ascynchronous Serial Port*******//
  	SYNC = 0; //Setting Asynchronous Mode, ie UART
  	SPEN = 1; //Enables Serial Port
  	//_____Asynchronous serial port enabled_______//
  	
  	
  	// Set The RX-TX Pins to be in UART mode (not io)
  	TRISC7 = 1;// RX Pin set as input		// As stated in the datasheet
 	TRISC6 = 0;// As stated in the datasheet
 	/*
	 giao tiep giua 2 pic -->TRISC6=1;
	 giao tiep giua pic va may tinh --->TRISC6=0;// TX Pin set as output
	 */
	 
 	//--[ Enable UART Receiving Interrupts ]--
	//RCIE = 1; // UART Receving Interrupt Enable Bit
	//PEIE = 1; // Peripherals Interrupt Enable Bit
	//GIE = 1; // Global Interrupt Enable Bit
	//------------------------------------------
	
	
	//**Lets prepare for transmission & reception**//
 	CREN = 1;//enable reception	-----// Enable Data Continous Reception-
  	TXEN = 1; //Enables Transmission
 	//__UART module up and ready for transmission and reception__//
 	
 	
 	//**Select 8-bit mode**//  
    TX9   = 0;    // 8-bit reception selected
    RX9   = 0;    // 8-bit reception mode selected
    //__8-bit mode selected__//     
    
 	return 1; //Returns 1 to indicate Successful Completion
	}
	
	return 0;//Returns 0 to indicate UART initialization failed
}

/*
void UART_Init()
{
    TRISC=0x80;      // Configure Rx pin as input and Tx as output  
  	TXSTA=0x20;      // Asynchronous mode, 8-bit data & enable transmitter
	RCSTA=0x90;      // 8-bit continous receive enable
	SPBRG=31;        // 9600 Baud rate at 20MHz
}
*/

/*
void UART_Init(const uint32_t baud_rate)
{
  int16_t n = ( _XTAL_FREQ / (16 * baud_rate) ) - 1;
  
  if (n < 0)
    n = 0;
 
  if (n > 255)  // low speed
  {
    n = ( _XTAL_FREQ / (64 * baud_rate) ) - 1;
    if (n > 255)
      n = 255;
    SPBRG = n;
    TXSTA = 0x20;  // transmit enabled, low speed mode
  }
 
  else   // high speed
  {
    SPBRG = n;
    TXSTA = 0x24;  // transmit enabled, high speed mode
  }
 
  RCSTA = 0x90;  // serial port enabled, continues receive enabled
 
}
*/


//Sending Data Through UART

/*Checking Transmit Register*/
char UART_TX_Empty()
{
  return TRMT;	//a flag that sets if the data has been sent
}

/*Writing a Character*/
void UART_Write_Char(char data)// UART_send_char
{
  while(!TRMT);// hold the program till TX buffer is free
  TXREG = data;//Load the transmitter buffer with the received value
}
/*
//used to transmit a char through UART module 
//Send Char
void UART_Tx_Char(char ch)
{
	TXREG=ch;        	// load the chr the to be transmitted into transmit reg
   	while(TXIF==0);  	// Wait till the transmitter register becomes empty
	TXIF=0;        		// Clear transmitter flag
    TXREG=ch;        	// load the chr the to be transmitted into transmit reg
}
*/


/*Writing Text*/
void UART_Write_String(char *text)//UART_send_string
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write_Char(text[i]);
}

/*
//Function to convert string to byte
void UART_send_string(char* st_pt)
{
    while(*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}
 */


/*
//used to transmit the ASCII string through UART
void UART_Tx_String(char *string_ptr)
{
  	while(*string_ptr)
   	UART_Tx_Char(*string_ptr++);
}
*/

/*
//used to transmit a 5-digit integer(0-65535)

//ex:
//if the number is 12345 then 12345 is transmitted.
//if the number is 123 then 00123 is transmitted.
void UART_Tx_Number(unsigned int num)
{
 
	   UART_Tx_Char((num/10000)+0x30);
	   num=num%10000;
 
	   UART_Tx_Char((num/1000)+0x30);
	   num=num%1000;
 
	   UART_Tx_Char((num/100)+0x30);
	   num=num%100;
 
	   UART_Tx_Char((num/10)+0x30);
 
       UART_Tx_Char((num%10)+0x30);
}
*/


//Receiving Data Through UART

/*
 ex:
 * 
    if(UART_Data_Ready())   // if a character available
    {
        r_data = UART_Read_Char();
    }
  
 se lien tuc goi ham UART_Read_Char()
 */
/*Data Received or Not*/

//this function returns 1 if there is data (in the receiver buffer)
// 	ready for reading, returns 0 if there is no data.
char UART_Data_Ready()
{
   return RCIF;// return RCIF bit (register PIR1, bit 5)
}

//**Function to get one byte of date from UART**//
char UART_Read_Char()//UART_get_char()   
{
    /*
     gia tri tra ve phai la bien toan cuc
     */
    while (RCIF == 0) ;  // wait for data receive
    
    if(OERR) // if there is overrun error 
    { // clear overrun error bit
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
        
    return RCREG; //receive the value and send it to main function
}
/*
//used to receive a char from UART module
//Receive Char
char UART_Rx_Char()
{
   while(RCIF==0);    // Wait till the data is received 
    RCIF=0;            // Clear receiver flag
   return(RCREG);        // Return the received data to calling function
}
*/

//used to receive a ASCII string through UART till the carriage_return/New_line
//Reading Text
void UART_Read_String(char *Output, unsigned int length)
{
	int i;
	for(i=0;i<length;i++)
		*(Output+i) = UART_Read_Char();
}
/*
//Once the carriage_return/New_line is encountered the loop is breaked and the String is NULL terminated.
//The received char is ECHOED back, if not required then comment UART_TxChar(ch) in the code.
//BackSlash is not taken care.
*/
/*
void UART_Rx_String(char *string_ptr)
{
	char ch;
	while(1)
	{
		ch=UART_Rx_Char();    //Receive a char
		UART_Tx_Char(ch);     //Echo back the received char
	
		if((ch=='\r') || (ch=='\n')) //read till enter key is pressed
		{				     //once enter key is pressed
			*string_ptr=0;            //null terminate the string
			break;			     //and break the loop
		}
		*string_ptr=ch;                //copy the char into string.
		string_ptr++;			    //and increment the pointer
	}
 }
*/
