#include"uart_pic_pic.h"

//Initializing UART
    //baudrate = 9600  is OK
    //_XTAL_FREQ = 20MHz
/*
void UART_Init()
{
    TRISC=0x80;      // Configure Rx pin as input and Tx as output  
  	TXSTA=0x20;      // Asynchronous mode, 8-bit data & enable transmitter
	RCSTA=0x90;      // 8-bit continous receive enable
	SPBRG=31;        // 9600 Baud rate at 20MHz
}
*/
char UART_Init( unsigned long uart_baudRate )
{
    unsigned int x;
	
	x = (_XTAL_FREQ - uart_baudRate*64)/(uart_baudRate*64);//SPBRG for Low Baud Rate
	if(x>255)									//If High Baud Rage Required
	{
		x = (_XTAL_FREQ - uart_baudRate*16)/(uart_baudRate*16);//SPBRG for High Baud Rate
		BRGH = 1;									 //Setting High Baud Rate
	}
	else 
		BRGH = 0;  //setting low speed baud rate
	
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
	//RCIE = 1; // UART Receving Interrupt Enable Bit
	//PEIE = 1; // Peripherals Interrupt Enable Bit
	//GIE = 1; // Global Interrupt Enable Bit
	//------------------------------------------
	
 	//CREN = 1;//enable reception	-----// Enable Data Continous Reception-
  	TXEN = 1; //Enables Transmission
 	CREN = 1;
    
 	//**Select 8-bit mode**//  
    TX9   = 0;    // 8-bit reception selected
    RX9   = 0;    // 8-bit reception mode selected
    //__8-bit mode selected__//     
    
 	return 1; //Returns 1 to indicate Successful Completion
	}
	
	return 0;//Returns 0 to indicate UART initialization failed
}


/////////////////////////////////////////////////////////////
/////////////////Sending Data Through UART//////////////////////
////////////////////////////////////////////////////////////////

//Checking Transmit Register
char UART_TX_Empty()
{
    return TRMT;	//a flag that sets if the data has been sent
}

//Writing a Character
void UART_Write_Char(char ch)// UART_send_char//Tx
{
    while(TXIF==0);  	// Wait till the transmitter register becomes empty
    TXREG=ch;        	// load the chr the to be transmitted into transmit reg

}

//Writing Text
void UART_Write_String(char *text)//UART_send_string
{
  for(int i=0;text[i]!='\0';i++)
	  UART_Write_Char(text[i]);
//dung con tro  
//  while(*text) //if there is a char
//        UART_Write_Char(*text++); //process it as a byte data
}

//////////////////////////////////////////////////////////////////
//////////////////Receiving Data Through UART///////////////////
////////////////////////////////////////////////////////////////////////


/*
//Data Received or Not
*
The following function can be used to check whether the data is ready to read from the Receive Register. 
It uses the flag bit RCIF which will be set when the data reception is completed. 
*/
/*
 ex:
 * 
    if(UART_Data_Ready())   // if a character available
    {
        r_data = UART_Read_Char();
    }
  
 se lien tuc goi ham UART_Read_Char()
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
//**Function to get one byte of date from UART**//
char UART_Read_Char()//UART_get_char()   
{
    /*
     gia tri tra ve phai la bien toan cuc
     */
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    
    while(RCIF==0);  // Wait till the data is received 
    RCIF=0;            // Clear receiver flag
     
    return RCREG; //receive the value and send it to main function
}

/*
//Reading Text
 * 
The following function can be used to read a desired length of text or sequence of characters continuously.
 */

void UART_Read_String(char *Output, unsigned int length)// UART_Rx_String
{
	unsigned int i;
	for(int i=0;i<length;i++)
		Output[i] = UART_Read_Char();
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




