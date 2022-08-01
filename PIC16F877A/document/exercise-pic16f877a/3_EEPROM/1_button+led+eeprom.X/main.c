/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 3:20 AM
 */

#include <xc.h>
#include <stdint.h>
#include "internal_eeprom.h"

#define _XTAL_FREQ 4000000//4MHz

//--[ Pin Definitions ]--
#define Read RB0 // Read EEPROM Memory Blocks
#define W_3 RB1 // Write 0x03
#define W_5 RB2 // Write 0x05
#define W_7 RB3 // Write 0x07
//================================
//--[ Function Declarations ]--
//void EEPROM_Write(uint8_t, uint8_t);
//uint8_t EEPROM_Read(uint8_t);
//================================
void main(void)
{
  ADCON1=0x07;
  //--[ IO Pins Configuration ]--
  TRISB = 0x0F; // Push Buttons (Inputs)
  
  TRISD = 0x00; // Output LEDs
  PORTD = 0x00; // Initially OFF
 
  uint8_t Address=0;
  
  while(1)
  {
    if(W_3) // Write 0x03
    {
      EEPROM_Write(Address++, 3);
      __delay_ms(500);
    }
    if(W_5) // Write 0x05
    {
      EEPROM_Write(Address++, 5);
      __delay_ms(500);
    }
    if(W_7) // Write 0x07
    {
      EEPROM_Write(Address++, 7);
      __delay_ms(500);
    }
    if(Address == 3)
      Address = 0;
    
    if(Read == 1)
    {
      // Read The EEPROM Data Out To PORTD LEDs
      for (uint8_t i=0; i<3; i++)
      {
        PORTD = EEPROM_Read(i);
        __delay_ms(1000);
      }
      
      PORTD=0x00;
    }
  }
  return;
}
