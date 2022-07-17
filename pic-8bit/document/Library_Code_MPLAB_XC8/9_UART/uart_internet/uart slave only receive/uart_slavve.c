#include"uart salve.h"

void UART_RX_Init(unsigned long uart_baudRate)
{
  uint16_t x;
  x = (_XTAL_FREQ - uart_baudRate*64)/(uart_baudRate*64); // Low Baud Rate
  if(x>255)
  {
    x = (_XTAL_FREQ - uart_baudRate*16)/(uart_baudRate*16); // High Baud Rate
    BRGH = 1;
  }
  if (x<=255)
  {
    SPBRG = x; //Writing SPBRG Register
  }
  // Enable The Ascynchronous Serial Port
  SYNC = 0;
  SPEN = 1;
  // Set The RX-TX Pins to be in UART mode (not io)
  TRISC6 = 1; // As stated in the datasheet
  TRISC7 = 1; // As stated in the datasheet
  //--[ Enable UART Receiving Interrupts ]--
  RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
  //------------------
  CREN = 1; // Enable Data Continous Reception
}
 
uint8_t UART_Read_Char()
{
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    while(!RCIF); // Wait Untill a Data Frame is Received
    return RCREG;
}

/*
//Data Received or Not
*
The following function can be used to check whether the data is ready to read from the Receive Register. 
It uses the flag bit RCIF which will be set when the data reception is completed. 
*/
char UART_Data_Ready()
{
    return RCIF;
}


 
void UART_Read_String(uint8_t *Output, uint16_t length)
{
  uint16_t i;
  for(int i=0;i<length;i++)
    Output[i] = UART_Read_Char();
}