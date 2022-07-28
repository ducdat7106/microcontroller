#include"eeprom_internal.h"

//write 1 byte to eeprom
void EEPROM_Write_Char(uint8_t Address, uint8_t Data)
{
	while(EECON1bits.WR); // Waits Until Last Attempt To Write Is Finished
	EEADR = Address;      // Writes The Addres To Which We'll Wite Our Data
	EEDATA = Data;        // Write The Data To Be Saved
	EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
	EECON1bits.WREN = 1;  // Enable The Operation !
	INTCONbits.GIE = 0;   // Disable All Interrupts Untill Writing Data Is Done
	EECON2 = 0x55;        // Part Of Writing Mechanism..
	EECON2 = 0xAA;        // Part Of Writing Mechanism..
	EECON1bits.WR = 1;    // Part Of Writing Mechanism..
	INTCONbits.GIE = 1;   // Re-Enable Interrupts
	EECON1bits.WREN = 0;  // Disable The Operation
	EECON1bits.WR = 0;    // Ready For Next Writing Operation
}


/*
Description:This function is used to Write a String at specified EEPROM_address.
	EEPROM_WriteByte() function is called to write a byte at a time.
	Source(RAM) and destination(EEPOM) address are incremented each time.
	Above Operation is carried out till Null char is identified.
I/P Arguments:
	char,-->eeprom_address where the String is to be written.
	char*-->Pointer to String which has to be written.
Return value : none
NOTE:

Null char is also written into the eeprom.
*/

/*
void EEPROM_Write_String(unsigned char eeprom_address, unsigned char * source_address)
  {
    do
 	{
 	  EEPROM_Write_1_Byte(eeprom_address,*source_address); //Write a byte from RAM to EEPROM
 	    source_address++;				          //Incerement the RAM Address
 		eeprom_address++;					    //Increment the Eeprom Address
 	  }while(*(source_address-1)!=0);
  }
*/

//write string to eeprom
void EEPROM_Write_String(uint8_t Address, const char Data[] )
{
    unsigned int len;
    unsigned char i;
    len = strlen(Data);
    for(i=0;i<len;i++)
    {
        EEADR = Address + i;
        EEDATA = Data[i];
        EEPROM_Write_Char(Address, Data[i]);
    }
}

/*
Description: This function is used to write N-bytes of data at specified EEPROM_address.
	
	EEPROM_WriteByte() function is called to write a byte at atime.
	
	Source(RAM) and destination(EEPROM) address are incremented after each write
	
	NoOfBytes is Decemented each time a byte is written.
	
	Above Operation is carried out till all the bytes are written(NoOfBytes!=0).

I/P Arguments:
	
	char,-->eeprom_address from where the N-bytes are to be written.
	
	char*-->Pointer to the N-bytes of data to be written.
	
	char --> Number of bytes to be written.
	
Return value : none
*/
void EEPROM_Write_N_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
{
  while(NoOfBytes !=  0)
   {
        EEPROM_Write_Char(EepromAddr,*RamAddr); //Write a byte from RAM to EEPROM
        EepromAddr++;				   //Incerement the Eeprom Address
        RamAddr++;				   //Increment the RAM Address
        NoOfBytes--;			   //Decrement NoOfBytes after writing each Byte
	}
}


//read 1 byte from eeprom
uint8_t EEPROM_Read_Char(uint8_t Address)
{
	uint8_t Data;
	EEADR = Address;      // Write The Address From Which We Wonna Get Data
	EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
	EECON1bits.RD = 1;    // Start The Read Operation
	Data = EEDATA;        // Read The Data
	return Data;
}

/*
Description:This function is used to Read a String from specified EEPROM_address.
	EEPROM_ReadByte() function is called to read a byte at a time.
	Source(EEPROM) and destination(RAM) address are incremented each time.
	Above Operation is carried out till Null char is identified.
I/P Arguments:
	char,--> eeprom_address from where the String is to be read.
	char*--> Pointer into which the String is to be read.
Return value : none
*/
void EEPROM_Read_String(unsigned char eeprom_address, unsigned char *destination_address)
{
   char eeprom_data;
 
    do
    {
        eeprom_data = EEPROM_Read_Char(eeprom_address); //Read a byte from EEPROM to RAM
        *destination_address = eeprom_data;	       //Copy the data into String Buffer
        destination_address++;				 //Incerement the RAM Address
        eeprom_address++;				 //Increment the eeprom Address
    }while(eeprom_data!=0);
}

/*
Description: This function is used to Read N-bytes of data from specified EEPROM_address.
	EEPROM_ReadByte() func is called to read a byte at a time.
	Source(RAM) and destination(EEPROM) address are incremented each time.
	NoOfBytes is Decemented after a byte is read.
	Above Operation is carried out till all the bytes are read(NoOfBytes!=0).
I/P Arguments:
	char,-->eeprom_address from where the N-bytes is to be read.
	char*-->Pointer into which the N-bytes of data is to be read.
	char --> Number of bytes to be Read
Return value : none
*/
void EEPROM_Read_N_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
{
	while(NoOfBytes !=  0)
	{
        *RamAddr = EEPROM_Read_Char(EepromAddr);//Read a byte from EEPROM to RAM
        EepromAddr++;				    //Incerement the Eeprom Address
        RamAddr++;			          //Increment the RAM Address
        NoOfBytes--;			    //Decrement NoOfBytes after Reading each Byte
	}
}

