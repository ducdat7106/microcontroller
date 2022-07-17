
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


//Slave Data Receiving Code on Interrupt
//(General ISR For I2C Slave. it could be for write, read, or overflow error)
short receiver;
void __interrupt() I2C_Slave_Read()
{ 
    if(PIR1bits.SSPIF == 1)
    {
       SSPCONbits.CKP = 0;// strecth the clock signal to low
       
       if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))// check errors such as collision and buffer overrflow
       {
             receiver = SSPBUF;  // read the value from SSPBUF to clear it 
             SSPCONbits.SSPOV = 0; // Clear the overflow flag
             SSPCONbits.WCOL = 0;   // Clear the collision bit
             SSPCONbits.CKP = 1;    // Release Clock from low
       }

      if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) // Read
       {
           receiver = SSPBUF;// Read The Last Byte To Clear The Buffer
           while(!BF);
           PORTD = SSPBUF;// Read The Received Data Byte
           SSPCONbits.CKP = 1;
           SSPM3 = 0;
       }
       else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)// Write
       {
           receiver = SSPBUF;// Read The Last Byte To Clear The Buffer
           BF = 0;
           SSPBUF = PORTB ; // Write Your Data 
           SSPCONbits.CKP = 1;
           while(SSPSTATbits.BF);
       }
       
       SSPIF = 0;
    }
}
/*
 SSPCON1 configures I2C Slave mode with a 7-bit address
        by setting  SSPM3: SSPM0 = 0110.
 */
void I2C_Slave_Init(unsigned char Address)
{
    TRISC3 = 1;     // Set RC3/SDA pins as a input pin
    TRISC4 = 1;     // Set RC4/SCL pins as a input pin
    SSPADD = Address;  // store the address of slave in SSPADD register
    SSPSTAT = 0x80; //  set standard slew rate
    SSPCON = 0x36; // Select & Enable I2C (Slave Mode)
    SSPCON2 = 0x01; // Enable Clock Stretching
    PIR1bits.SSPIF = 0;      // Enbable Interrupts
    PIE1bits.SSPIE = 1;     // Enable  PICI2C module interrrupt
    INTCONbits.PEIE = 1;    // Enable peripheral interrupt
    INTCONbits.GIE = 1;    // Enable global interrupt

}

void main()
{
  nRBPU = 0;            //Enables PORTB internal pull up resistors
  TRISB = 0xFF;         //PORTB as input
  TRISD = 0x00;         //PORTD as output
  PORTD = 0x00;         //All LEDs OFF
  I2C_Slave_Init(0x30); //Initialize as a I2C Slave with address 0x30
  while(1);
}