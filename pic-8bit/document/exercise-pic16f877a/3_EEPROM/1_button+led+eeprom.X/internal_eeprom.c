#include<xc.h>
#include <stdint.h>

void EEPROM_Write(uint8_t Address, uint8_t Data)
{
  while(EECON1bits.WR); // Waits Until Last Attempt To Write Is Finished
  EEADR = Address;      // Writes The Addres To Which We'll Wite Our Data
  EEDATA = Data;        // Write The Data To Be Saved
  EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
  EECON1bits.WREN = 1;  // Enable The Operation !
  INTCONbits.GIE = 0;   // Disable All Interrupts Untill Writting Data Is Done
  EECON2 = 0x55;        // Part Of Writing Mechanism..
  EECON2 = 0xAA;        // Part Of Writing Mechanism..
  EECON1bits.WR = 1;    // Part Of Writing Mechanism..
  INTCONbits.GIE = 1;   // Re-Enable Interrupts
  EECON1bits.WREN = 0;  // Disable The Operation
  EECON1bits.WR = 0;    // Ready For Next Writting Operation
}

uint8_t EEPROM_Read(uint8_t Address)
{
  uint8_t Data;
  EEADR = Address;      // Write The Address From Which We Wonna Get Data
  EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
  EECON1bits.RD = 1;    // Start The Read Operation
  Data = EEDATA;        // Read The Data
  return Data;
}
