// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <pic16f877a.h>

#define _XTAL_FREQ 8000000

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//char UART_Init(const long int baudrate)
//{
//  unsigned int x;
//  x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);   //SPBRG for Low Baud Rate
//  if(x>255)                                       //If High Baud Rage Required
//  {
//    x = (_XTAL_FREQ - baudrate*16)/(baudrate*16); //SPBRG for High Baud Rate
//    BRGH = 1;                                     //Setting High Baud Rate
//  }
//  if(x<256)
//  {
//    SPBRG = x;                                    //Writing SPBRG Register
//    SYNC = 0;                                     //Setting Asynchronous Mode, ie UART
//    SPEN = 1;                                     //Enables Serial Port
//    TRISC7 = 1;                                   //As Prescribed in Datasheet
//    TRISC6 = 1;                                   //As Prescribed in Datasheet
//    CREN = 1;                                     //Enables Continuous Reception
//    TXEN = 1;                                     //Enables Transmission
//    return 1;                                     //Returns 1 to indicate Successful Completion
//  }
//  return 0;                                       //Returns 0 to indicate UART initialization failed
//}
//
//char UART_TX_Empty()
//{
//  return TRMT;
//}
//
//void UART_Write(char data)
//{
//  while(!TRMT);
//  TXREG = data;
//}
//
//void UART_Write_Text(char *text)
//{
//  int i;
//  for(i=0;text[i]!='\0';i++)
//    UART_Write(text[i]);
//}


//Initialize I2C Module as Master
void I2C_Master_Init(unsigned char c)
{
  SSPCON = 0b00101000;            //SSP Module as Master
  SSPCON2 = 0;
  SSPADD = (unsigned char)(_XTAL_FREQ/(4000*c))-1; //Setting Clock Speed
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

void read_button_display_led();
void write_data_display_led();

void main()
{
    nRBPU = 0;                    //Enable PORTB internal pull up resistor
    TRISB = 0xFF;                 //PORTB as input
    TRISD = 0x00;                 //PORTD as output
    PORTD = 0x00;                 //All LEDs OFF
    I2C_Master_Init(100);      //Initialize I2C Master with 100KHz clock
  
    while(1)
    {
        //read_button_display_led();
        write_data_display_led();
    }
}

void read_button_display_led()
{
    I2C_Master_Start();         //Start condition
    I2C_Master_Write(0x30);     //7 bit address + Write
    I2C_Master_Write(PORTB);    //Write data
    I2C_Master_Stop();          //Stop condition

    __delay_ms(200);

    I2C_Master_Start();         //Start condition
    I2C_Master_Write(0x31);     //7 bit address + Read
    PORTD = I2C_Master_Read(); //Read + Acknowledge
    I2C_Master_NACK();
    I2C_Master_Stop();          //Stop condition
    __delay_ms(200);   
}

void write_data_display_led()
{
    static unsigned char value=0;
    I2C_Master_Start();     // I2C Start Sequence
    I2C_Master_Write(0x30);  // I2C Slave Device Address + Write
    I2C_Master_Write(value++);   // The Data To Be Sent
    I2C_Master_Stop();      // I2C Stop Sequence
    __delay_ms(500);
}