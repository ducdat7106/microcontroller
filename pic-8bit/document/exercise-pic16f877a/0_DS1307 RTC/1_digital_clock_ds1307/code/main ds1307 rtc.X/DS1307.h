/* 
 * File:   DS1307.h
 * Author: NGUYEN DUC DAT
 *
 * Created on 5 January, 2022, 3:08 PM
 */

#ifndef DS1307_H
#define	DS1307_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include <stdint.h>
#include<stdio.h>
#include<string.h>
#include"i2c_master.h"


#define RTC_I2C_START    I2C_Start
#define RTC_I2C_RESTART  I2C_Restart
#define RTC_I2C_WRITE    I2C_Write_Char
#define RTC_I2C_READ     I2C_Read_Char
#define RTC_I2C_STOP     I2C_Stop

#define DS1307_ADDRESS      0xD0
#define DS1307_REG_SECONDS  0x00
#define DS1307_REG_CONTROL  0x07

//format 12h --> bit 6 == 1
//format 24h --> bit 6 == 0
#define TimeFormat12        0x40//bit 6 (0x40 = 0100.0000)
    
//if format 12h
    //bit 5 == 1 -->PM
    //bit 5 == 0 -->AM
#define AMPM                0x20//bit 5 (0x20 = 0010.0000)


typedef enum
{
  OUT_OFF = 0x00,
  OUT_ON  = 0x80,
  OUT_1Hz = 0x10,
  OUT_4096Hz  = 0x11,
  OUT_8192Hz  = 0x12,
  OUT_32768Hz = 0x13
} SQWE;//tan so

typedef enum
{
  SUNDAY = 1,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} RTC_DOW;//weekdays

char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


typedef enum
{
  JANUARY = 1,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
} RTC_Month;

typedef struct rtc_tm
{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  RTC_DOW dow;
  uint8_t day;
  RTC_Month month;
  uint8_t year;
} RTC_Time;


///////////////////////// All Functions ///////////////////////////////////////
                                                               
uint8_t bcd_to_decimal(uint8_t number);                        
uint8_t decimal_to_bcd(uint8_t number);                        


int IsItPM(int hour_ );


/*
 void RTC_Set(RTC_Time *time_t): this function sets time and date 
 (writes time and date to the DS1307) where the variable time_t of type struct (structure)
 which collects the following unsigned 8-bit integer variables:
 
seconds, minutes, hours, dow, day, month and year.
Where dow is day of the week (Monday, Tuesday ?) and day is month day.
seconds and minutes range: 0 - 59
hours range: 0 - 23 (24-hour format)
dow range: 1 - 7 (1 equals Sunday, 2 equals Monday )
day range: 1 - 31 (depends on month)
month range: 1 - 12 (1 equals January)
year range: 0 - 99.
 */
void RTC_Set(RTC_Time *time_t);                              

/*
 reads time and date from the DS1307,
 this function returns them as a variable of type struct (same as the previous function).
 */
RTC_Time *RTC_Get();                                          
                                   
/*
 uint8_t RTC_Read_Reg(uint8_t reg_address): this function returns the value stored 
 in register of address reg_address.
 */
uint8_t RTC_Read_Reg(uint8_t reg_address);                     

/*
 void RTC_Write_Reg(uint8_t reg_address, uint8_t reg_value): writes reg_value to register of address reg_address.
 */
void RTC_Write_Reg(uint8_t reg_address, uint8_t reg_value);    








void OSC_Enable();    //enables the DS1307 oscillator.                                   
void OSC_Disable();   //disables the DS1307 oscillator.    


/*
 void SQWE_Set(SQWE pin_out): this function configures the SQW/OUT pin of the DS1307, 
 where pin_out is one of the following:
OUT_OFF: output is off (internally attached to ground)
OUT_ON: output is on (internally floating)
OUT_1Hz: output is square wave with frequency equals to 1Hz
OUT_4096Hz: output is square wave with frequency equals to 4096Hz
OUT_8192Hz: output is square wave with frequency equals to 8192Hz
OUT_32768Hz: output is square wave with frequency equals to 32768Hz
 */
void SQWE_Set(SQWE pin_out);                                  


uint8_t OSC_Status();                                         
                                                              
/////////////////////////////////////////////////////////////////


#ifdef	__cplusplus
}
#endif

#endif	/* DS1307_H */

