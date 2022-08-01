#include"DS1307.h"

// convert BCD to decimal function
uint8_t bcd_to_decimal(uint8_t number) {
  return(uint8_t)((number >> 4) * 10 + (number & 0x0F));
}
 
// convert decimal to BCD function
uint8_t decimal_to_bcd(uint8_t number) {
  return(uint8_t)(((number / 10) << 4) + (number % 10));
}
 /*
  //lcd display rtc time function
void lcd_DisplayRtcTime(char hour,char min,char sec)
{
    lcd_Writedata(((hour>>4) & 0x0f) + 0x30);
    lcd_Writedata((hour & 0x0f) + 0x30);
    lcd_Writedata(':');
 
    lcd_Writedata(((min>>4) & 0x0f) + 0x30);
    lcd_Writedata((min & 0x0f) + 0x30);
    lcd_Writedata(':');
 
    lcd_Writedata(((sec>>4) & 0x0f) + 0x30);
    lcd_Writedata((sec & 0x0f) + 0x30);
 
 }
 
 
 // lcd display rtc date function
void lcd_DisplayRtcDate(char day,char month,char year)
 {
     lcd_Writedata(((day>>4) & 0x0f) + 0x30);
     lcd_Writedata((day & 0x0f) + 0x30);
     lcd_Writedata('/');
 
     lcd_Writedata(((month>>4) & 0x0f) + 0x30);
     lcd_Writedata((month & 0x0f) + 0x30);
     lcd_Writedata('/');
 
     lcd_Writedata(((year>>4) & 0x0f) + 0x30);
     lcd_Writedata((year & 0x0f) + 0x30);
 
 }
  */


// sets time and date
void RTC_Set(RTC_Time *time_t)
{
  uint8_t sec_reg = RTC_Read_Reg(DS1307_REG_SECONDS);

  // convert decimal to BCD
  time_t->day     = decimal_to_bcd(time_t->day);
  time_t->month   = decimal_to_bcd(time_t->month);
  time_t->year    = decimal_to_bcd(time_t->year);
  time_t->hours   = decimal_to_bcd(time_t->hours);
  time_t->minutes = decimal_to_bcd(time_t->minutes);
  time_t->seconds = decimal_to_bcd(time_t->seconds);
  // end conversion
  
  // test if oscillator is disabled (CH bit = 1)
  if(sec_reg & 0x80)
    time_t->seconds |= 0x80;

  // write data to the RTC chip
  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_ADDRESS);
  RTC_I2C_WRITE(DS1307_REG_SECONDS);
  RTC_I2C_WRITE(time_t->seconds);
  RTC_I2C_WRITE(time_t->minutes);
  RTC_I2C_WRITE(time_t->hours);
  RTC_I2C_WRITE(time_t->dow);
  RTC_I2C_WRITE(time_t->day);
  RTC_I2C_WRITE(time_t->month);
  RTC_I2C_WRITE(time_t->year);
  RTC_I2C_STOP();
}

RTC_Time c_time;

// reads time and date
RTC_Time *RTC_Get()
{
  RTC_I2C_START();
  
  RTC_I2C_WRITE(DS1307_ADDRESS);
  RTC_I2C_WRITE(DS1307_REG_SECONDS);
  
  RTC_I2C_RESTART();
  
  RTC_I2C_WRITE(DS1307_ADDRESS | 0x01);
  
  c_time.seconds = RTC_I2C_READ(0) & 0x7F;
  c_time.minutes = RTC_I2C_READ(0);
  c_time.hours   = RTC_I2C_READ(0);
  c_time.dow     = RTC_I2C_READ(0);
  c_time.day     = RTC_I2C_READ(0);
  c_time.month   = RTC_I2C_READ(0);
  c_time.year    = RTC_I2C_READ(1);
  
  RTC_I2C_STOP();

  // convert BCD to decimal
  c_time.seconds = bcd_to_decimal(c_time.seconds);
  c_time.minutes = bcd_to_decimal(c_time.minutes);
  c_time.hours   = bcd_to_decimal(c_time.hours);
  c_time.dow     = bcd_to_decimal(c_time.dow);
  c_time.day     = bcd_to_decimal(c_time.day);
  c_time.month   = bcd_to_decimal(c_time.month);
  c_time.year    = bcd_to_decimal(c_time.year);
  // end conversion

  return &c_time;
}

// writes 'reg_value' to register of address 'reg_address'
void RTC_Write_Reg(uint8_t reg_address, uint8_t reg_value)
{
  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_ADDRESS);
  RTC_I2C_WRITE(reg_address);
  RTC_I2C_WRITE(reg_value);
  RTC_I2C_STOP();
}

// returns the value stored in register of address 'reg_address'
uint8_t RTC_Read_Reg(uint8_t reg_address)
{
  uint8_t reg_data;

  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_ADDRESS);
  RTC_I2C_WRITE(reg_address);
  RTC_I2C_RESTART();
  RTC_I2C_WRITE(DS1307_ADDRESS | 0x01);
  reg_data = RTC_I2C_READ(1);
  RTC_I2C_STOP();

  return reg_data;
}


///Check the AMPM bit in hour register (bit 5)
int IsItPM(int hour_){  //co phai PM hay khong
    if( (hour_ & (AMPM) ) == AMPM)
        return 1;//PM
    else
        return 0;//AM
}




// sets SQWE pin output
void SQWE_Set(SQWE pin_out)
{
  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_ADDRESS);
  RTC_I2C_WRITE(DS1307_REG_CONTROL);
  RTC_I2C_WRITE(pin_out);
  RTC_I2C_STOP();
}

// enables RTC oscillator
void OSC_Enable()
{
  uint8_t sec_reg = RTC_Read_Reg(DS1307_REG_SECONDS);
  sec_reg &= 0x7F;
  RTC_Write_Reg(DS1307_REG_SECONDS, sec_reg);
}

// disables RTC oscillator
void OSC_Disable()
{
  uint8_t sec_reg = RTC_Read_Reg(DS1307_REG_SECONDS);
  sec_reg |= 0x80;
  RTC_Write_Reg(DS1307_REG_SECONDS, sec_reg);
}

// returns RTC oscillator status (true: enabled and false: disabled)
uint8_t OSC_Status()
{
  uint8_t sec_reg = RTC_Read_Reg(DS1307_REG_SECONDS);
  if(sec_reg & 0x80)
    return 1;//false;

  return 0;//true;
}

// end of driver code.
