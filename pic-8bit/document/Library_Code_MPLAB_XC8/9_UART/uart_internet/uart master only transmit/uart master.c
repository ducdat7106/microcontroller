#include"uart_master.h"


void UART_TX_Init( unsigned long uart_baudRate )
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
    SPBRG = x;  //Writing SPBRG Register
  }
  //--[ Enable The Ascynchronous Serial Port ]--
  SYNC = 0;
  SPEN = 1;
  //--[ Set The RX-TX Pins to be in UART mode (not io) ]--
  TRISC6 = 1;   // As stated in the datasheet
  TRISC7 = 1;   // As stated in the datasheet
  TXEN = 1;     // Enable UART Transmission
}
 
void UART_Write_Char(char data)
{
  while(!TRMT);
  TXREG = data;
}
 
 
/*Checking Transmit Register*/
char UART_TX_Empty()
{
  return TRMT;
}


void UART_Write_String(char *text)
{
  uint16_t i;
  for(i=0;text[i]!='\0';i++)
    UART_Write_Char(text[i]);
}

