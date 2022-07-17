/*
File : ADC.h
Athor : NGUYEN DUC DAT
Time : 8_2020
*/
#include <xc.h>

void ADC_Init();
unsigned int ADC_Read(unsigned char channel);


/*
0x81 = 0b01000001
0x80 = 0b11000000
*/
void ADC_Init()
{
   ADCON0 = 0x81; //ADC ON and Fosc/16 is selected
   ADCON1 = 0x80; //Internal reference voltage is selected
}


/*
0xC5 = 0x11000101

channel = {0,1,2,3,4,5,6,7};

funstion return value = { 0, 1, 2, ...., 1022, 1023};
*/
unsigned int ADC_Read(unsigned char channel)
{
   if(channel > 7)
     return 0;
	//ADCON0 = ( (1 << ADON) | (channel << 3) );//select required channel end turn ON Adc
  
   ADCON0 &= 0xC5;	//Clearing the Channel Selection Bits
   ADCON0 |= channel<<3;	//Setting the required Bits
   
   __delay_ms(2);	//Acquisition time to charge hold capacitor
   
   GO_nDONE = 1;	//Initializes A/D Conversion
   while(GO_nDONE);	//Wait for A/D Conversion to complete
   
   return ((ADRESH<<8)+ADRESL);	//Returns Result
}

