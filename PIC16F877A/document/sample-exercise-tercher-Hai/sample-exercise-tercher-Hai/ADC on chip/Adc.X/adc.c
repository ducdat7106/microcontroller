
#include <xc.h>

void InitADC(void)
{
    ADCON1 = 0b11000100;   // Right Justified, OSC/64; AN0-2.
    ADCON0 =0x80;
   // ADON=1;
}

unsigned int ReadAdc(unsigned char Channel)
{
    unsigned int value;
    switch(Channel)
	{
	case 0: CHS0 = 0;  CHS1 = 0;  CHS2 = 0; break;
    case 1: CHS0 = 1;  CHS1 = 0;  CHS2 = 0;
    }
    ADON=1;
    __delay_us(5);
    GO_DONE=1;
    while(GO_DONE);
    value=(unsigned int)ADRESH*256+ADRESL;
    ADON=0;
    //value=1023;
    return value;
}