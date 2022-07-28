/*
 * File:   main_khoa cua.c
 * Author: Nguyen Duc Dat
 *  
 * Created on 26 December, 2021, 8:59 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include"eeprom_internal.h"
#include"i2c_lcd.h"
#include"i2c_master.h"
#include"keypad_4x4.h"



char code1[15] ;
char user1[4] = {50, 51, 52, 53};//2345
unsigned char m=0;
int  j, cnt = 0;
unsigned char w1;


void LOCK_Enter();
void LOCK_Read();
void LOCK_Write();
void LOCK_Change();
void LOCK_Run();

void System_Init()
{
    ADCON1 = 0x07;
    
    Keypad_Init();
    
    LCD_Init(100000);
}

void main(void) 
{
    System_Init();
    
    LCD_Set_Cursor(2,4);
    LCD_Write_String("Door System 1");       
    __delay_ms(1000);
    LCD_Clear();    
    
    while(1)
    {
        LOCK_Run();
    }
    return;
}


void LOCK_Enter()
{
    char kp;//ma thap phan: DEC
    
    kp = 'n';       //Reset key code variable

    //wait for key to be pressed and released
    do{
       kp = Keypad_Switch_Press_Scan();       // store key code in kp variable
    }while (kp == 'n');

    //prepare value for output, transform key to it's ASCII value
    switch (kp)
    {
        case '1': kp = 49; break; // 1
        case '2': kp = 50; break; // 2
        case '3': kp = 51; break; // 3
        //case  4: kp = 65; break; // A for 4x4 pad
        case '4': kp = 52; break; // 4
        case '5': kp = 53; break; // 5
        case '6': kp = 54; break; // 6
        //case  8: kp = 66; break; // B for 4x4 pad
        case '7': kp = 55; break; // 7
        case '8': kp = 56; break; // 8
        case '9': kp = 57; break; // 9
        //case 12: kp = 67; break; // C for 4x4 pad
        case 'C': kp = 43; break; // C
        case '0': kp = 48; break; // 0
        case '=': kp = 61; break; // =
        //case 16: kp = 67; break; // D for 4x4 pad
    }

    code1[m] = kp;
    LCD_Set_Cursor(2, m+1);
    LCD_Write_Char(code1[m]); //Print key ASCII value on Lcd     
    m++;
}

//20ms delay function no need of it

void LOCK_Read()    //read data from eeprom
{      
    __delay_ms(20);
    user1[0] = EEPROM_Read_Char(0x00);            // Read data from address 0
    __delay_ms(20);
    user1[1] = EEPROM_Read_Char(0x01);            // Read data from address 1
    __delay_ms(20);
    user1[2] = EEPROM_Read_Char(0x02);            // Read data from address 2
    __delay_ms(20);
    user1[3] = EEPROM_Read_Char(0x03);            // Read data from address 3
    __delay_ms(20);
}

void LOCK_Write()   //write data to eeprom
{       
    __delay_ms(20);
    EEPROM_Write_Char(0x00,code1[0]);           // Write data to address 0
    __delay_ms(20);
    EEPROM_Write_Char(0x01,code1[1]);           // Write data to address 1
    __delay_ms(20);
    EEPROM_Write_Char(0x02,code1[2]);           // Write data to address 2
    __delay_ms(20);
    EEPROM_Write_Char(0x03,code1[3]);           // Write data to address 3
    __delay_ms(20);
}


void LOCK_Change()
{
    LCD_Clear(); 
    LCD_Set_Cursor(1,1);
    LCD_Write_String( "CHANGE CODE" );
    __delay_ms(1000);
    
    LCD_Clear();           // clear display
    LCD_Set_Cursor(1,1);
    LCD_Write_String( "Enter New Code:" );

    m = 0;

    LOCK_Enter();
    LOCK_Enter();
    LOCK_Enter();
    LOCK_Enter();


    LOCK_Write();
    LOCK_Read();

    LCD_Clear();           // clear display
    LCD_Set_Cursor(1,1);
    LCD_Write_String("New Code Set");
    __delay_ms(2000);
    LCD_Clear();
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String(code1);
    
    LCD_Set_Cursor(2,1);
    LCD_Write_String(user1);
    __delay_ms(1000);
    LCD_Clear();
}

void LOCK_Run()
{
 L2:   LCD_Clear();
    LCD_Set_Cursor(2,3);
    LCD_Write_String("Press C ");
    
    m=0;
    
    LOCK_Enter();
    if(code1[0] == 43)  // C
    {
        LCD_Clear();
        LCD_Set_Cursor(1,1);
        LCD_Write_String("Input Number:");
        
        m=0;
        
        LOCK_Enter();//vao 5 ky tu
        LOCK_Enter();
        LOCK_Enter();
        LOCK_Enter();
        LOCK_Enter();

        if(code1[0] == '1' && code1[1] == '2'  && code1[2] == '3' && code1[3] == '4' && code1[4] == '5' )     // master code
        {
            LOCK_Enter();
            if(code1[5] == 61)      // =
            {
                LOCK_Change(); 
                goto L2;
            }
            
        }
        else if(code1[0]==user1[0] && code1[1]==user1[1] && code1[2]==user1[2] && code1[3]==user1[3] && code1[4]==61)     // save password verification
        {
            LCD_Clear();
            LCD_Set_Cursor(1,4);
            LCD_Write_String("Door open"); //Door Open
            __delay_ms(3000);
            
            /*
            EEPROM_Read_Char(0x21);
            w1 = 1;
            __delay_ms(20);
            EEPROM_Write_Char(0x21, w1);
            __delay_ms(20);
            EEPROM_Read_Char(0x21);
            */
            /*
             //move stepper motor to ON position
            PORTC=0x03;
            __delay_ms(500);
            PORTC=0x06;
             __delay_ms(500);
            PORTC=0x0C;
             __delay_ms(500);
            PORTC=0x09;
             __delay_ms(500);
             
            __delay_ms(5000);
            
            */
            LCD_Clear();
            LCD_Set_Cursor(1,4);
            LCD_Write_String("Door Close");
             __delay_ms(3000);
            
            /*
            EEPROM_Read_Char(0x21);
            w1 = 0;
            __delay_ms(20);
            EEPROM_Write_Char(0x21, w1);
            __delay_ms(20);
            EEPROM_Read_Char(0x21);
            */
            
            /*
            //move stepper motor to OFF position
            PORTC=0x0C;
            __delay_ms(500);
            PORTC=0x06;
            __delay_ms(500);
            PORTC=0x03;
            __delay_ms(500);
            PORTC=0x09;
            __delay_ms(500);

            __delay_ms(2000);
            //goto L1;
             */
        }
        else
        {
            cnt++;
            LCD_Clear();     //clear display
            LCD_Set_Cursor(1,1);
            LCD_Write_String("Wrong Password");
            __delay_ms(2000);
        }
                               
        if(cnt>=3)
            cnt=0;
        
    }
    
    
}