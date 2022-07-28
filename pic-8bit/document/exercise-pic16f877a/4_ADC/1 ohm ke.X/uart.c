
#include <xc.h>
#define STX '{'
//#define STX  0x7b
#define ETX  0x7d
char commbuffer[20];

void Init_uart(void)
{
    TXSTA=0x20;  // TXEN=1 BRGH=0
    RCSTA=0x90;// SPEN CREN
    SPBRG=25;// 9600 16mHZ
    RCIE=1;
}
void Send_data(unsigned int Value)
{
    unsigned char i=0;
    unsigned int k=0;
    unsigned int temp;
    /*
	commbuffer[0]='{';    
	commbuffer[1]=Value/100+0x30; //'1';
    commbuffer[2]='.';
    k=Value%100;
	commbuffer[3]=k/10+0x30;
	commbuffer[4]=k%10+0x30;
	commbuffer[5]=ETX;
    commbuffer[6]='\r';//0x0d;
    */
    Value=Value%100000;
    commbuffer[0]='{';
    commbuffer[1]=Value/10000+0x30;
    temp = Value%10000;
    commbuffer[2]= temp/1000+0x30;
    temp = temp % 1000;
    commbuffer[3] = temp/100+0x30;
    temp = temp%100;
    commbuffer[4] = temp/10+0x30;
    commbuffer[5] = temp%10+0x30;
    commbuffer[6]='}';
    commbuffer[7]='\r';//0x0d;
    
    for(i=0;i<8;i++)
    {
      TXREG=commbuffer[i];
      while(TRMT==0);      
    }
}