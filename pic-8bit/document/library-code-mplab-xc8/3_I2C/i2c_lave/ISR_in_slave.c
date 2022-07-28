#include<xc.h>

unsigned char RX_Data = 0x00;

char Dummy;

/* Write The ISR Handler For I2C Slave

(General ISR For I2C Slave. it could be for write, read, or overflow error) */

void __interrupt() ISR(void)
{
  if(SSPIF == 1)
  {
    CKP = 0; // Hold (Stretch) The Clock Line LOW
    if (SSPOV || WCOL) // Bus Collision or Buffer Overflow
    {
      Dummy = SSPBUF; // Read The Last Byte To Clear The Buffer
      SSPOV = 0;           // Clear the overflow flag
      WCOL = 0;            // Clear the collision bit
      CKP = 1;             // Release Clock Line SCL
    }
    
    
    if(R_nW && !D_nA) // Read  //If last byte was Address + Read
    {
      Dummy = SSPBUF; // Read The Last Byte To Clear The Buffer
      while(!BF);
      RX_Data = SSPBUF;    // Read The Received Data Byte
      CKP = 1; // Release Clock Line SCL
    }
    
    
    else if(!R_nW && !D_nA) // Write   //If last byte was Address + Write
    {
      Dummy = SSPBUF; // Read The Last Byte To Clear The Buffer
      BF = 0;
      SSPBUF = Dummy;      // Write Your Data (REMOVE THE DUMMY)
      CKP = 1; // Release Clock Line SCL
      while(BF);
    }
    SSPIF = 0;
  }
}
