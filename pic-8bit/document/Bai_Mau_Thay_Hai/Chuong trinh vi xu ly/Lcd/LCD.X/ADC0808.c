#include "ADC0808.h"


void InitADC(void)
{
	TRISC=0b00001000;  //EOC input RC4
	TRISB=0xff;// Make Inputs 	
}



unsigned int ReadADC(unsigned char Channel)
{
	unsigned int i = 0;
	unsigned int ADC_value = 0;

     i='a';

	// Select Channel
	switch(Channel)
	{
	case AN0: Add_C = 0;  Add_B = 0;  Add_A = 0; break;
	case AN1: Add_C = 0;  Add_B = 0;  Add_A = 1; break;
	case AN2: Add_C = 0;  Add_B = 1;  Add_A = 0; break;
	case AN3: Add_C = 0;  Add_B = 1;  Add_A = 1; break;
	case AN4: Add_C = 1;  Add_B = 0;  Add_A = 0; break;
	case AN5: Add_C = 1;  Add_B = 0;  Add_A = 1; break;
	case AN6: Add_C = 1;  Add_B = 1;  Add_A = 0; break;
	case AN7: Add_C = 1;  Add_B = 1;  Add_A = 1; break;
	}	   

	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	ALE = 1;						// Enable Address Latch
	CLK = 1; 						// Make CLK High
	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	CLK = 0; 						// Make CLK Low
	START = 1;						// Start ADC Conversion
	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	CLK = 1; 						// Make CLK High
	ALE = 0;						// Disable Address Latch
	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	CLK = 0; 						// Make CLK Low
	START = 0;						// Complete the start pulse

	for(i=0;i<2000;i++)
	{
		CLK = !CLK;					// Toggle Clock
		__delay_us(HalfCycleDelay);	// 250kHz Frequency

		if(!EOC)		  			// Wait for EOC to be low
			break;
	}

	for(i=0;i<2000;i++)
	{
		CLK = !CLK;					// Toggle Clock
		__delay_us(HalfCycleDelay);	// 250kHz Frequency

 		if(EOC)					   	// Wait for EOC to be High	
			break;
	}

	CLK = 0; 						// Make CLK Low
	OE = 1;							// Enable Output
	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	CLK = 1; 						// Make CLK High
	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	CLK = 0; 						// Make CLK Low
	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	CLK = 1; 						// Make CLK High

	ADC_value = Data_Bus;			// Read value

	__delay_us(HalfCycleDelay);		// 250kHz Frequency
	OE = 0;							// Disable Output
	CLK = 0; 						// Make CLK Low
	__delay_us(HalfCycleDelay);		// 250kHz Frequency

	return ADC_value;		 		// Return ADC value
}