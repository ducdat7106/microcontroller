/*
 * File:   main ds3231.c
 * Author: Nguyen Duc Dat
 *
 * Created on 17 December, 2021, 5:34 PM
 */


#include <xc.h>
#include<stdint.h>

#include"config.h"
#include"i2c_master.h"
#include"lcd.h"

// button definitions
#define button1      RB1   // button B1 is connected to RB1 pin
#define button2      RB2   // button B2 is connected to RB2 pin
#define button3      RB3   // button B2 is connected to RB3 pin
#define LED_PIN      RB4   // Alarm LED is connected to RB4 pin
 
char Time[]     = "  :  :  ",
     Date[] = "  /  /20  ",
     Alarm1[]   = "A1:   :  :00", Alarm2[]   = "A2:   :  :00",
     Temperature[] = "T:   .   C";
uint8_t  i, second, minute, hour, w_day, m_day, month, year,
         alarm1_minute, alarm1_hour, alarm2_minute, alarm2_hour,
         status_reg, alarm1_status, alarm2_status;
 
void external_interrupt()
{
    INTE=1; // enable external interrupt
    INTF=0; // clear external interrupt flag bit
    GIE=1;  // enable global interrupts
    INTEDG = 0; // set external Interrupt on falling edge
}

// external interrupt ISR
void __interrupt() EXT(void)
{
  if (INTF)
  {
    LED_PIN = 1;
    INTF = 0;
  }
}


// function for button debounce
__bit debounce (uint8_t button)
{
  uint8_t count = 0;
  for(uint8_t i = 0; i < 5; i++)
  {
    switch (button)
    {
      case 1: if (button1 == 0)
                count++;
                break;
      case 3: if (button3 == 0)
                count++;
                break;
      default:  break;
    }
    __delay_ms(10);
  }
  if(count > 2)  return 1;
  else           return 0;
}


/********************** RTC chip functions *********************/
// convert BCD to decimal function
uint8_t bcd_to_decimal(uint8_t number)
{
  return((number >> 4) * 10 + (number & 0x0F));
}
 
// convert decimal to BCD function
uint8_t decimal_to_bcd(uint8_t number)
{
  return(((number / 10) << 4) + (number % 10));
}
 
void RTC_read()    // read current time & date from RTC chip
{
  I2C_Start();           // start I2C
  I2C_Write_Char(0xD0);       // RTC chip address
  I2C_Write_Char(0);          // send register address
  I2C_Restart();  // restart I2C
  I2C_Write_Char(0xD1);       // initialize data read
  second = I2C_Read_Char();  I2C_ACK(); // read seconds from register 0
  minute = I2C_Read_Char();  I2C_ACK();// read minutes from register 1
  hour   = I2C_Read_Char();  I2C_ACK();// read hour from register 2
  w_day  = I2C_Read_Char();  I2C_ACK();// read day of the week from register 3
  m_day  = I2C_Read_Char();  I2C_ACK();// read date from register 4
  month  = I2C_Read_Char();  I2C_ACK();// read month from register 5
  year   = I2C_Read_Char();  I2C_NACK();// read year from register 6
  I2C_Stop();            // stop I2C
}
 
void alarms_read_display()   // read and display alarm1 and alarm2 data function
{
  uint8_t control_reg, temperature_lsb;
  int8_t temperature_msb;
  I2C_Start();          // start I2C
  I2C_Write_Char(0xD0);      // RTC chip address
  I2C_Write_Char(0x08);      // send register address (alarm1 minutes register)
  I2C_Restart(); // restart I2C
  I2C_Write_Char(0xD1);      // initialize data read
  alarm1_minute = I2C_Read_Char();   I2C_ACK();// read alarm1 minutes
  alarm1_hour   = I2C_Read_Char();   I2C_ACK();// read alarm1 hours
  I2C_Read_Char();                   I2C_ACK();// skip alarm1 day/date register
  alarm2_minute = I2C_Read_Char();   I2C_ACK();// read alarm2 minutes
  alarm2_hour   = I2C_Read_Char();   I2C_ACK();// read alarm2 hours
  I2C_Read_Char();                   I2C_ACK();// skip alarm2 day/date register
  control_reg = I2C_Read_Char();     I2C_ACK();// read control register
  status_reg  = I2C_Read_Char();     I2C_ACK();// read status register
  I2C_Read_Char();                   I2C_ACK();// skip aging offset register
  temperature_msb = I2C_Read_Char(); I2C_ACK();// read temperature MSB
  temperature_lsb = I2C_Read_Char(); I2C_NACK();// read temperature LSB
  I2C_Stop();                    // stop I2C
  // convert BCD to decimal
  alarm1_minute = bcd_to_decimal(alarm1_minute);
  alarm1_hour   = bcd_to_decimal(alarm1_hour);
  alarm2_minute = bcd_to_decimal(alarm2_minute);
  alarm2_hour   = bcd_to_decimal(alarm2_hour);
  // end conversion
  // update Alarm1 and Alarm2
  Alarm1[8]     = alarm1_minute % 10  + '0';
  Alarm1[7]     = alarm1_minute / 10  + '0';
  Alarm1[5]     = alarm1_hour   % 10  + '0';
  Alarm1[4]     = alarm1_hour   / 10  + '0';
  Alarm2[8]     = alarm2_minute % 10  + '0';
  Alarm2[7]     = alarm2_minute / 10  + '0';
  Alarm2[5]     = alarm2_hour   % 10  + '0';
  Alarm2[4]     = alarm2_hour   / 10  + '0';
  alarm1_status = control_reg & 0x01;      // read alarm1 interrupt enable bit (A1IE) from RTC chip control register
  alarm2_status = (control_reg >> 1) & 0x01; // read alarm2 interrupt enable bit (A2IE) from RTC chip control register
  if(temperature_msb < 0){
    temperature_msb *= -1;
    Temperature[2] = '-';
  }
  else
    Temperature[2] = ' ';
  temperature_lsb >>= 6;
  Temperature[4] = temperature_msb % 10  + '0';
  Temperature[3] = temperature_msb / 10  + '0';
  if(temperature_lsb == 0 || temperature_lsb == 2){
    Temperature[7] = '0';
    if(temperature_lsb == 0) Temperature[6] = '0';
    else                     Temperature[6] = '5';
  }
  if(temperature_lsb == 1 || temperature_lsb == 3){
    Temperature[7] = '5';
    if(temperature_lsb == 1) Temperature[6] = '2';
    else                     Temperature[6] = '7';
  }
  Temperature[8]  = 223;   // put degree symbol (°)
  LCD_Set_Cursor(1, 11);
  LCD_Write_String(Temperature);  // print temperature
  LCD_Set_Cursor(3, 1);
  LCD_Write_String(Alarm1);       // print Alarm1
  if(alarm1_status) {
    LCD_Set_Cursor(3, 18);
    LCD_Write_String("ON ");      // if A1IE = 1 print 'ON'
  }
  else {
    LCD_Set_Cursor(3, 18);
    LCD_Write_String("OFF");   // if A1IE = 0 print 'OFF'
  }
  LCD_Set_Cursor(4, 1);
  LCD_Write_String(Alarm2);    // print Alarm2
  if(alarm2_status){
    LCD_Set_Cursor(4, 18);
    LCD_Write_String("ON ");   // if A2IE = 1 print 'ON'
  }
  else {
    LCD_Set_Cursor(4, 18);
    LCD_Write_String("OFF");   // if A2IE = 0 print 'OFF'
  }
}
 
void w_day_display()    // print day of the week
{
  LCD_Set_Cursor(2, 1);
  switch(w_day)
  {
    case 1:  LCD_Write_String("Sun"); break;
    case 2:  LCD_Write_String("Mon"); break;
    case 3:  LCD_Write_String("Tue"); break;
    case 4:  LCD_Write_String("Wed"); break;
    case 5:  LCD_Write_String("Thu"); break;
    case 6:  LCD_Write_String("Fri"); break;
    default: LCD_Write_String("Sat");
  }
}
 
// display time and date function
void RTC_display()
{
  // convert data from BCD format to decimal format
  second = bcd_to_decimal(second);
  minute = bcd_to_decimal(minute);
  hour   = bcd_to_decimal(hour);
  m_day  = bcd_to_decimal(m_day);
  month  = bcd_to_decimal(month);
  year   = bcd_to_decimal(year);
  // end conversion
  // update time
  Time[7] = second % 10  + '0';
  Time[6] = second / 10  + '0';
  Time[4] = minute % 10  + '0';
  Time[3] = minute / 10  + '0';
  Time[1] = hour   % 10  + '0';
  Time[0] = hour   / 10  + '0';
  // update date
  Date[9] = year  % 10 + '0';
  Date[8] = year  / 10 + '0';
  Date[4] = month % 10 + '0';
  Date[3] = month / 10 + '0';
  Date[1] = m_day  % 10 + '0';
  Date[0] = m_day  / 10 + '0';
 
  LCD_Set_Cursor(1, 1);    // go to column 1, row 1
  LCD_Write_String(Time);   // print time
  LCD_Set_Cursor(2, 5);    // go to column 1, row 2
  LCD_Write_String(Date);   // print date
  w_day_display();   // print day of the week
 
}
 
// make editing parameter blinks function
void blink()
{
  uint8_t j = 0;
  while( j < 100 && (button1 || i >= 5) && button2 && (button3 || i < 5) )
  {
    j++;
    __delay_ms(5);
  }
}
 
// edit time and date function
uint8_t edit(uint8_t x, uint8_t y, uint8_t parameter)
{
  while(debounce(1) || debounce(3));  // call debounce function (wait for B1 & B3 to be released)
 
  while(1) {
 
    while(!button2)    // if button B2 is pressed
    {
      parameter++;
      if(((i == 0) || (i == 5)) && parameter > 23)   // if hours > 23 ==> hours = 0
        parameter = 0;
      if(((i == 1) || (i == 6)) && parameter > 59)   // if minutes > 59 ==> minutes = 0
        parameter = 0;
      if(i == 2 && parameter > 31)   // if date > 31 ==> date = 1
        parameter = 1;
      if(i == 3 && parameter > 12)   // if month > 12 ==> month = 1
        parameter = 1;
      if(i == 4 && parameter > 99)   // if year > 99 ==> year = 0
        parameter = 0;
      if(i == 7 && parameter > 1)    // for alarms ON or OFF (1: alarm ON, 0: alarm OFF)
        parameter = 0;
 
      LCD_Set_Cursor(x, y);
      LCD_Write_Char(parameter / 10 + '0');
      LCD_Write_Char(parameter % 10 + '0');
 
      if(i >= 5){
        RTC_read();     // read data from RTC chip
        RTC_display();  // display time and date
      }
      __delay_ms(200);
    }
 
    LCD_Set_Cursor(x, y);
    LCD_Write_String("  ");  // print 2 spaces
    blink();
 
    LCD_Set_Cursor(x, y);
    LCD_Write_Char(parameter / 10 + '0');
    LCD_Write_Char(parameter % 10 + '0');
    blink();
 
    if(i >= 5)
    {
      RTC_read();
      RTC_display();
    }
 
    if((!button1 && i < 5) || (!button3 && i >= 5))     // if B1 or B3 is pressed
    {
      i++;   // increment 'i' for the next parameter
      return parameter;     // return parameter value and exit
    }
  }
}
 
uint8_t on_off(uint8_t x, uint8_t y, uint8_t al)
{
  while(debounce(3));  // call debounce function (wait for B3 to be released)
  while (1)
  {
    while(!button2)    // if button B2 is pressed
    {
      al = (!al) & 0x01;
      LCD_Set_Cursor(x, y);
      if(al == 1)  LCD_Write_String("ON ");
      else         LCD_Write_String("OFF");
      __delay_ms(200);
    }
 
    LCD_Set_Cursor(x, y);
    LCD_Write_String("   ");  // print 3 spaces
    blink();
 
    LCD_Set_Cursor(x, y);
    if(al == 1)  LCD_Write_String("ON ");
    else         LCD_Write_String("OFF");
    blink();
 
    RTC_read();
    RTC_display();
 
    if(!button3)
    if(debounce(3))
    {
     return al; 
    }
  }
}
 
/********************** end RTC chip functions *****************/
 


void main(void) 
{
    ADCON1 =0x07;
    
    PORTB  = 0;      // PORTB initial state
    TRISB  = 0x0F;   // configure RB0 ~ 3 as input pins
    // enable RB0, RB1, RB2 and RB3 internal pull ups
    nRBPU  = 0;      // clear RBPU bit (OPTION_REG.7)
    
    external_interrupt();
    
    LCD_Init();
    
    I2C_Master_Init(100000);   // initialize I2C bus with clock frequency of 100kHz
    
    while(1)
    {
    if(!button1)     // if button B1 is pressed
    if(debounce(1))   // call debounce function (make sure if B1 is pressed)
    {
      i = 0;
      hour   = edit(1, 1, hour);
      minute = edit(1, 4, minute);
 
      while(debounce(1));  // call debounce function (wait for button B1 to be released)
 
      while(1)
      {
        while(!button2)    // if button RB2 button is pressed
        {
          w_day++;    // increment day
          if(w_day > 7) w_day = 1;
          w_day_display();
          __delay_ms(200);
        }
 
        LCD_Set_Cursor(2, 1);   //row=2, column=1
        LCD_Write_String("   ");  // print 3 spaces
        blink();           // call blink function
        w_day_display();
        blink();           // call blink function
        if(!button1)       // if button B1 is pressed
        if(debounce(1))    // call debounce function (make sure if B1 is pressed)
          break;
      }
 
      m_day  = edit(2,  5, m_day);
      month  = edit(2,  8, month);
      year   = edit(2, 13, year);
 
      while(debounce(1));  // call debounce function (wait for button B1 to be released)
 
      // convert decimal to BCD
      minute = decimal_to_bcd(minute);
      hour   = decimal_to_bcd(hour);
      m_day  = decimal_to_bcd(m_day);
      month  = decimal_to_bcd(month);
      year   = decimal_to_bcd(year);
      // end conversion
 
      // write data to DS3231 RTC
      I2C_Start();         // start I2C
      I2C_Write_Char(0xD0);     // RTC chip address
      I2C_Write_Char(0);        // send register address
      I2C_Write_Char(0);        // reset seconds and start oscillator
      I2C_Write_Char(minute);   // write minute value to RTC chip
      I2C_Write_Char(hour);     // write hour value to RTC chip
      I2C_Write_Char(w_day);    // write day of the week value to RTC chip
      I2C_Write_Char(m_day);    // write date (day of the month) value to RTC chip
      I2C_Write_Char(month);    // write month value to RTC chip
      I2C_Write_Char(year);     // write year value to RTC chip
      I2C_Stop();          // stop I2C
 
      __delay_ms(200);
 
    }
 
    if(!button3)     // if RB3 button is pressed
    if(debounce(3))  // call debounce function (make sure if B3 is pressed)
    {  
      i = 5;
      alarm1_hour   = edit(3, 5, alarm1_hour);
      alarm1_minute = edit(3, 8, alarm1_minute);
      alarm1_status = on_off(3, 18, alarm1_status);
      i = 5;
      alarm2_hour   = edit(4, 5, alarm2_hour);
      alarm2_minute = edit(4, 8, alarm2_minute);
      alarm2_status = on_off(4, 18, alarm2_status);
 
      while(debounce(3));  // call debounce function (wait for button B3 to be released)
      // convert decimal to BCD
      alarm1_minute = decimal_to_bcd(alarm1_minute);
      alarm1_hour   = decimal_to_bcd(alarm1_hour);
      alarm2_minute = decimal_to_bcd(alarm2_minute);
      alarm2_hour   = decimal_to_bcd(alarm2_hour);
      // end conversion
      // write alarms data to DS3231
      I2C_Start();      // start I2C
      I2C_Write_Char(0xD0);  // RTC chip address
      I2C_Write_Char(7);     // send register address (alarm1 seconds)
      I2C_Write_Char(0);     // write 0 to alarm1 seconds
      I2C_Write_Char(alarm1_minute);   // write alarm1 minutes
      I2C_Write_Char(alarm1_hour);     // write alarm1 hours
      I2C_Write_Char(0x80);            // alarm1 when hours, minutes, and seconds match
      I2C_Write_Char(alarm2_minute);   // write alarm2 minutes
      I2C_Write_Char(alarm2_hour);     // write alarm2 hours
      I2C_Write_Char(0x80);            // alarm2 when hours and minutes match
      I2C_Write_Char(4 | alarm1_status | (alarm2_status << 1));    // write data to control register (enable interrupt when alarm)
      I2C_Write_Char(0);     // clear alarm flag bits
      I2C_Stop();       // stop I2C
      __delay_ms(200);  // wait 200ms
    }
    if(!button2 && LED_PIN){   // when button B2 pressed with alarm (Reset and turn OFF the alarm)
      LED_PIN = 0;             // turn OFF alarm indicator
      I2C_Start();             // start I2C
      I2C_Write_Char(0xD0);         // RTC chip address
      I2C_Write_Char(0x0E);         // send register address (control register)
      // write data to control register (Turn OFF the occurred alarm and keep the other as it is)
      I2C_Write_Char(4 | ((!(status_reg & 1)) & alarm1_status) | (((!((status_reg >> 1) & 1)) & alarm2_status) << 1));
      I2C_Write_Char(0);    // clear alarm flag bits
      I2C_Stop();      // stop I2C
    }
 
    RTC_read();             // read time and date from RTC chip
    alarms_read_display();  // read and display alarms
    RTC_display();          // print time & date
 
    __delay_ms(50);   // wait 50 ms
 
  }
    
    return;
}

