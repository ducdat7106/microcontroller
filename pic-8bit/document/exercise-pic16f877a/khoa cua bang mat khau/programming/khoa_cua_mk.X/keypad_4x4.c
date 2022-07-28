#include"keypad_4x4.h"

// the keypad initialization which will redirect the port as output and input
void Keypad_Init()
{
    Keypad_PORT_Direction = 0xF0;      // Last 4 pins input, First 4 pins output
    Keypad_PORT           = 0x00;      // Set Keypad port pin values zero
    OPTION_REGbits.nRBPU = 0;          //enable PORTB pull-up //    or   //OPTION_REG &= 0x7F;
}

/*
 In each step we will make the row X1, X2, X3, and X4 as 0 and reading the Y1, Y2, Y3 and Y4 status.
 The delay is used for the debounce effect, when the switch is still pressed we will return the value associated with it. 
 When no switch are pressed we will return 'n'
 */
char Keypad_Scanner()  //quet ban phim, xem phim nao duoc nhan
{   
    int k = 0;//fix loi vong lap while bi trong--->ko co tac dung trong chuong trinh
    X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1;    
    if (Y_1 == 0) { while (Y_1==0) k=1; return '7'; }
    if (Y_2 == 0) { while (Y_2==0) k=1; return '8'; }
    if (Y_3 == 0) { while (Y_3==0) k=1; return '9'; }
    if (Y_4 == 0) { while (Y_4==0) k=1; return '/'; }

    X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1;    
    if (Y_1 == 0) { while (Y_1==0) k=1; return '4'; }
    if (Y_2 == 0) { while (Y_2==0) k=1; return '5'; }
    if (Y_3 == 0) { while (Y_3==0) k=1; return '6'; }
    if (Y_4 == 0) { while (Y_4==0) k=1; return 'x'; }

    X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1;    
    if (Y_1 == 0) { while (Y_1==0) k=1; return '1'; }
    if (Y_2 == 0) { while (Y_2==0) k=1; return '2'; }
    if (Y_3 == 0) { while (Y_3==0) k=1; return '3'; }
    if (Y_4 == 0) { while (Y_4==0) k=1; return '-'; }

    X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0;    
    if (Y_1 == 0) { while (Y_1==0) k=1; return 'C'; }
    if (Y_2 == 0) { while (Y_2==0) k=1; return '0'; }
    if (Y_3 == 0) { while (Y_3==0) k=1; return '='; }
    if (Y_4 == 0) { while (Y_4==0) k=1; return '+'; }
    
    k=0;
            
    return 'n';                  
}

//a switch press scan which will return the switch press status when called
// 1 cong tac bam quet
char Keypad_Switch_Press_Scan(void)    // Get key from user
{
    char key = 'n';              // Assume no key pressed
    while(key == 'n')              // Wait untill a key is pressed
        key = Keypad_Scanner();   // Scan the keys again and again
    return key;                  //when key pressed then return its value
}


///////////////////////////////// het cach 1 ///////////////////////////////////

/*
void Keypad_Init(void);
char KEY();

#define R1 RB0  //ROW1
#define R2 RB1
#define R3 RB2
#define R4 RB3
#define C1 RB4  //COLUMN1
#define C2 RB5
#define C3 RB6
#define C4 RB7


unsigned char keypad[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
unsigned char rowloc,colloc;

void Keypad_Init(void)
{
    Keypad_PORT_Direction = 0xF0;      // Last 4 pins input, First 4 pins output
    Keypad_PORT           = 0x00;      // Set Keypad port pin values zero
    //OPTION_REG &= 0x7F; //ENABLE PULL UP
    OPTION_REGbits.nRBPU = 0;//enable PORTB pull-up 
}

char KEY()
{
    Keypad_PORT = 0x00;
    while(C1&&C2&&C3&&C4);
    while(!C1||!C2||!C3||!C4) 
    {
        R1=0;R2=R3=R4=1;
        if(!C1||!C2||!C3||!C4) 
        {
            rowloc=0;
            break;
        }
        
        R2=0;R1=1;
        if(!C1||!C2||!C3||!C4) {
            rowloc=1;
            break;
        }
        
        R3=0;R2=1;
        if(!C1||!C2||!C3||!C4) 
        {
            rowloc=2;
            break;
        }
        
        R4=0; R3=1;
        if(!C1||!C2||!C3||!C4)
        {
            rowloc=3;
            break;
        }
    }
    if(C1==0&&C2!=0&&C3!=0&&C4!=0)
            colloc=0;
    else if(C1!=0&&C2==0&&C3!=0&&C4!=0)
            colloc=1;
    else if(C1!=0&&C2!=0&&C3==0&&C4!=0)
            colloc=2;
    else if(C1!=0&&C2!=0&&C3!=0&&C4==0)
            colloc=3;
    while(C1==0||C2==0||C3==0||C4==0);
    
    return (keypad[rowloc][colloc]);
}
*/
//////////////////////////// het cach 2 ////////////////////////////////////////