#pragma config FNOSC = PRI          // Oscillator Source Selection (Primary Oscillator XT, HS, EC)
#pragma config POSCMOD = HS         // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config JTAGEN = OFF         // JTAG Enable bit (JTAG is disabled)
#pragma config WINDIS = OFF         // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is disabled)

#include "xc.h"
#define FCY 8000000UL       //Instruction cycle frequency, Hz - required for __delayXXX() to work
#include "libpic30.h"       //__delayXXX() functions macros defined here
#include "lcd.h"
void Analog_Init(){
#ifdef __PIC24FJ1024GB610__
    AD1CON2bits.PVCFG =0;
#else
    AD1CON2bits.VCFG = 0;
#endif
    AD1CON3bits.ADCS = 0xFF;        // A/D Conversion Clock Select bits
    AD1CON1bits.SSRC = 0x00;        // Sample Clock Source Select bits
    AD1CON3bits.SAMC = 0x10;        // Auto-Sample Time Select bits 
    AD1CON1bits.FORM = 0x00;        // Data Output Format bits (00 = Absolute decimal result, unsigned, right justified)
    AD1CON2bits.SMPI = 0x00;        // Interrupt Sample/DMA Increment Rate Select bits
    AD1CON1bits.ADON = 0x01;        // A/D Operating Mode bit (0 = A/D Converter is off)
}

uint16_t Analog_Read(uint8_t channel){
    uint16_t i;
    switch(channel){
        case 4:
#ifdef __PIC24FJ1024GB610__
            ANSBbits.ANSB4=0;
#else 
            AD1PCFGbits.PCFG4=0;
#endif
            break;
        case 5:
#ifdef __PIC24FJ1024GB610__
            ANSBbits.ANSB5=0;
#else  
            AD1PCFGbits.PCFG5=0;
#endif
            break;
    }
    AD1CHS = channel;               // Select ADC channel 
    AD1CON1bits.SAMP = 1;           // ADC Sample-and-Hold amplifiers are sampling
    for(i = 0; i < 1000; i++){      // Waiting for sampling
        Nop();         
    }
    AD1CON1bits.SAMP = 0;           // ADC Sample-and-Hold amplifiers are sampling
    for(i = 0; i < 1000; i++){      // Waiting for sampling
        Nop();
    }
    while(!AD1CON1bits.DONE);       // Waiting until the Convertion is complete 
    return ADC1BUF0;                // return ADC value 
}
uint16_t LM35_TemperatureSensor(){
    uint16_t adcResult;
    uint16_t temp;
    adcResult = Analog_Read(4);     // Read Analog value from channel 4
    temp= (adcResult*330)/1024;     // Change Analog value to Temperature (oC)
    return temp;
}
uint16_t Variable_Resistor(){
    uint16_t adcResult;
    adcResult = Analog_Read(5);     // Read Analog value from channel 5
    return adcResult;
}
int main(void) {
    Analog_Init();                  // Analog Initialize
    LCD_Initialize();               // LCD Initialize 
    while(1){
        printf("Temp = %d oC \r\n", LM35_TemperatureSensor());  // print Temperature value in LCD
        printf("R = %d Ohm", Variable_Resistor());      // print Variable Resistor value in LCD
        __delay_ms(500);                                // Delay 0.5s
        LCD_ClearScreen();                              // Clear LCD Screen
    }
    return 0;
}
