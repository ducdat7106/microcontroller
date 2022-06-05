#include <REGX52.H>

#define BUTTON_ON  P1_0
#define BUTTON_OFF  P1_1

#define Turn_OFF 0xFF
#define Turn_ON 0x00

#define Led P0


P3 = 0x00;

	
void main()
{
    int flag=1;
    Led = Turn_OFF;
		
    while(1)
    {
        //Led=Turn_ON;
			if(BUTTON_ON == 0)
            flag=0;
            
        if(BUTTON_OFF==0)
            flag=1;
        
        if(flag==0)
            Led=Turn_ON;
        else
            Led=Turn_OFF;
				
				P3 = 0x00;
    }
}
