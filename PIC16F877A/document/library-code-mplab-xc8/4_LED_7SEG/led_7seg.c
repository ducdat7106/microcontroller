#include "led_7seg.h"

const uint8_t LED7_HEX[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,     //khong co cham
                            0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};    //co cham
    
unsigned char buffer[4];


void Led7_displayUnit(unsigned char number);
void Led7_addFloatToBuffer(double num);


void Led_7seg_Init()
{
	tris_led_7seg =0x00;
	led_7seg = 0x00;
	
	tris_enable_led1 = 0;
	tris_enable_led2 = 0;
	tris_enable_led3 = 0;
	tris_enable_led4 = 0;
	
	enable_led1 = 1;
	enable_led2 = 1;
	enable_led3 = 1;
	enable_led4 = 1;
}

char Led7_pointIndex(double num) 
{
    if (num > 99.9 && num <= 999.9) 
		return 1;
    else if (num > 9.9 && num <= 99.9) 
		return 2;
    else if (num >= 0 && num <= 9.9) 
		return 3;
		
    return 0;

}

void Led7_displayUnit(unsigned char number) 
{
	led_7seg = 0xff; //tat het tat ca cac led
    led_7seg = LED7_HEX[number];
}

void Led7_addFloatToBuffer(double num) 
{
    int newNum;
    char p = Led7_pointIndex(num);
    
    if (p == 0)
        newNum = (int) num;
    else if (p == 1)
        newNum = (int) (num * 10);
    else if (p == 2)
        newNum = (int) (num * 100);
    else if (p == 3)
        newNum = (int) (num * 1000);
        
    for (int i = 0; i < 4; i++)
	{
        buffer[i] = newNum % 10;
        newNum /= 10;
    }
    buffer[p] += 10;//hien thi dau cham o duoi
}

void Led_7seg_Display(double num) 
{
    Led7_addFloatToBuffer(num);

//    for (int i = 0; i < 4; i++) {
//        Led7_displayUnit(buffer[i]);
//        enable_led &= 0x08 >> i;
//        __delay_ms(2);
//    }
    
    enable_led = 0xFF;
    // bat den 1    
    enable_led1 = 0;
    Led7_displayUnit(buffer[3]);
    __delay_ms(3);
    enable_led1 = 1;
    
    // bat den 2    
    enable_led2 = 0;
    Led7_displayUnit(buffer[2]);
    __delay_ms(3);
   enable_led2 = 1;
   
    // bat den 3
    enable_led3 = 0;
    Led7_displayUnit(buffer[1]);
    __delay_ms(3);
   enable_led3 = 1;
   
    // bat den 4    
    enable_led4 = 0;
    Led7_displayUnit(buffer[0]);
    __delay_ms(3);
    enable_led4 = 1;
}
