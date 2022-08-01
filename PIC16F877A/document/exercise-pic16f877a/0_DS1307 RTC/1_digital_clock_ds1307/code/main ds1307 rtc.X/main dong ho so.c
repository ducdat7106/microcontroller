#include <xc.h>

#include"config.h"
#include"i2c_master.h"
#include"lcd.h"
#include"DS1307.h"

//Button definitions
#define button1      RB0   // button B1 is connected to RB0 pin
#define button2      RB1   // button B2 is connected to RB1 pin

/*variables declaration*/
uint8_t  i;

RTC_Time *mytime;


void rtc_print()
{
    char buffer[25];
 
    // print time
    sprintf( buffer, "%02u:%02u:%02u", (int)mytime->hours, (int)mytime->minutes, (int)mytime->seconds);
    
    if( ( (int)mytime->hours >= 1 ) && ( (int)mytime->hours <= 12) )//hour>=1 && hour <=12
        strcat(buffer, " AM");
    else
        strcat(buffer, " PM");
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String( buffer);
    
    // print date
    sprintf( buffer, "%s %02u-%02u-%02u", days[(int)mytime->dow-1], (int)mytime->day, (int)mytime->month, 2000 + (int)mytime->year);
    
    LCD_Set_Cursor(2,1);
    LCD_Write_String( buffer);
}

//A small function for button1 (B1) debounce
__bit debounce ()//giong while(button ==0); su suy doi/suy giam
{
  uint8_t count = 0;
  for(uint8_t i = 0; i < 5; i++) 
  {
    if (button1 == 0)
      count++;
    __delay_ms(10);
  }
  if(count > 2)  return 1;//nhan nut de hoat dong
  else           return 0;//nhan qua nhanh
}
 
// make editing parameter blinks function
void blink()//nhap nhay khi ca 2 nut khong bam
{
  uint8_t j = 0;
  while(j < 100 && button1 && button2) 
  {
    j++;
    __delay_ms(5);
  }
}
 
// Edit time and date function
uint8_t edit(uint8_t x, uint8_t y, uint8_t parameter)
{
  while(debounce());  // call debounce function (wait for B1 to be released)
 
  while(1) 
  {
 
    while(!button2)    // if button B2 is pressed
    {
      parameter++;
      if(i == 0 && parameter > 23)   // if hours > 23 ==> hours = 0
        parameter = 0;
      if(i == 1 && parameter > 59)   // if minutes > 59 ==> minutes = 0
        parameter = 0;
      if(i == 2 && parameter > 31)   // if date > 31 ==> date = 1
        parameter = 1;
      if(i == 3 && parameter > 12)   // if month > 12 ==> month = 1
        parameter = 1;
      if(i == 4 && parameter > 99)   // if year > 99 ==> year = 0
        parameter = 0;
 
      LCD_Set_Cursor(x, y);
      LCD_Write_Char((char)(parameter / 10 + '0') );
       LCD_Write_Char((char)(parameter % 10 + '0') );
      __delay_ms(200);
 
    }
 
    LCD_Set_Cursor(x, y);
    LCD_Write_String("  ");  // print 2 spaces
    blink();
 
    LCD_Set_Cursor(x, y);
    LCD_Write_Char((char)(parameter / 10 + '0'));
    LCD_Write_Char((char)(parameter % 10 + '0'));
    blink();
 
    if(!button1)     // if button B1 is pressed
    if(debounce())   // call debounce function (make sure if B1 is pressed)
    {
      i++;   // increment 'i' for the next parameter
      return parameter;     // return parameter value and exit
    }
  }
}
/********************** end RTC chip functions *****************/
 


/*************************** main function *********************/
void main(void)
{
    ADCON1 = 0x06;
 
    I2C_Master_Init(100000);   // initialize I2C bus with clock frequency of 100kHz
 
    LCD_Init();        // initialize LCD module
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String("CLOCK");
    __delay_ms(1000);
 
    while(1){
 
        if(!button1)     // if button B1 is pressed
            if(debounce())   // call debounce function (make sure if B1 is pressed)
            {
                i = 0;
                mytime->hours   = edit(1,  1, mytime->hours);
                mytime->minutes = edit(1, 4, mytime->minutes);
                mytime->day  = edit(2,  5,  mytime->day);
                mytime->month  = edit(2, 8, mytime->month);
                mytime->year   = edit(2, 13, mytime->year);

                while(debounce());  // call debounce function (wait for button B1 to be released)

                // write time and date to the RTC chip
                RTC_Set(mytime);

                __delay_ms(200);                
            }

        
        // read current time and date from the RTC chip
        mytime = RTC_Get();

        
        // print them
        rtc_print();
        __delay_ms(100);  // wait 100 ms

  }
}