#include"keypad_4x4.h"

/*
 * rows setup as output
 * columns setup as input 
 * 
 *keypad scan algorithm
 * 
 * 1. row=output & column =input
 * 2. check the row where the key is pessed in
 *    <Check Row=LOW logic & other Row = HIGH logic>
 *    Ex: Check 1st Row, we can put 0x7F = 0b0111.1111
 * 
 *     ==> return row value has pressed button
 * 
 * 3. Check the column where the key is pressed in
 * ==>return position of the pressed botton
 */

unsigned char keypad[4][4]={{'7','8','9','/'},
                            {'4','5','6','*'},
                            {'1','2','3','-'},
                            {'C','0','=','+'}};

unsigned char rowloc,colloc;


// the keypad initialization which will redirect the port as output and input
void Keypad_Init()
{
    OPTION_REGbits.nRBPU = 0;          //enable PORTB pull-up 
    
    //4 bit co trong so cao lam dau vao, 4 bit co trong so thap lam dau ra
    Keypad_PORT_Direction = 0xF0;      // Last 4 pins input, First 4 pins output
    
    Keypad_PORT           = 0x00;      // Set Keypad port pin values zero    
}

char Keypad_Find_1()
{
    Keypad_PORT = 0x00;
    
    //wait to when button was not pressed
    while(C1==1 && C2==1 && C3==1 && C4==1);//while(C1&&C2&&C3&&C4);
    
    //Find row pressed
    while(C1==0 || C2==0 || C3==0 || C4==0)//while(!C1||!C2||!C3||!C4) 
    {
        //row 1st
        R1=0;R2=R3=R4=1;
        if(C1==0 || C2==0 || C3==0 || C4==0)//if(!C1||!C2||!C3||!C4) 
        {
            rowloc=0;
        }
        
        //row 2nd
        R2=0;R1=R3=R4=1;
        if(C1==0 || C2==0 || C3==0 || C4==0)//if(!C1||!C2||!C3||!C4) 
        {
            rowloc=1;
        }
        
        //ROW 3rd
        R3=0;R1=R2=R4=1;
        if(C1==0 || C2==0 || C3==0 || C4==0)//if(!C1||!C2||!C3||!C4) 
        {
            rowloc=2;
        }
        
        //row 4rd
        R4=0; R1=R2=R3=1;
        if(C1==0 || C2==0 || C3==0 || C4==0)//if(!C1||!C2||!C3||!C4)
        {
            rowloc=3;
        }
    }
    
    
    //Find column pressed
    if(C1==0&&C2!=0&&C3!=0&&C4!=0)
            colloc=0;
    else if(C1!=0&&C2==0&&C3!=0&&C4!=0)
            colloc=1;
    else if(C1!=0&&C2!=0&&C3==0&&C4!=0)
            colloc=2;
    else if(C1!=0&&C2!=0&&C3!=0&&C4==0)
            colloc=3;
    
    //wait to when button khong duoc nha ra
    while(C1==0||C2==0||C3==0||C4==0);
    
    return (keypad[rowloc][colloc]);
}




/*
 In each step we will make the row X1, X2, X3, and X4 as 0 and reading the Y1, Y2, Y3 and Y4 status.
 The delay is used for the debounce effect, when the switch is still pressed we will return the value associated with it. 
 When no switch are pressed we will return 'n'
 */
char Keypad_Scanner()  //quet ban phim, xem phim nao duoc nhan
{   
    int k = 0;//fix loi vong lap while bi trong--->ko co tac dung trong chuong trinh
    R1 = 0; R2 = 1; R3 = 1; R4 = 1;    
    if (C1 == 0) { while (C1==0) k=1; return '7'; }
    if (C2 == 0) { while (C2==0) k=1; return '8'; }
    if (C3 == 0) { while (C3==0) k=1; return '9'; }
    if (C4 == 0) { while (C4==0) k=1; return '/'; }

    R1 = 1; R2 = 0; R3 = 1; R4 = 1;    
    if (C1 == 0) { while (C1==0) k=1; return '4'; }
    if (C2 == 0) { while (C2==0) k=1; return '5'; }
    if (C3 == 0) { while (C3==0) k=1; return '6'; }
    if (C4 == 0) { while (C4==0) k=1; return 'x'; }

    R1 = 1; R2 = 1; R3 = 0; R4 = 1;    
    if (C1 == 0) { while (C1==0) k=1; return '1'; }
    if (C2 == 0) { while (C2==0) k=1; return '2'; }
    if (C3 == 0) { while (C3==0) k=1; return '3'; }
    if (C4 == 0) { while (C4==0) k=1; return '-'; }

    R1 = 1; R2 = 1; R3 = 1; R4 = 0;    
    if (C1 == 0) { while (C1==0) k=1; return 'C'; }
    if (C2 == 0) { while (C2==0) k=1; return '0'; }
    if (C3 == 0) { while (C3==0) k=1; return '='; }
    if (C4 == 0) { while (C4==0) k=1; return '+'; }
    
    k=0;
            
    return 'n';                  
}

//a switch press scan which will return the switch press status when called
// 1 cong tac bam quet
char Keypad_Find_2()    // Get key from user
{
    char key = 'n';              // Assume no key pressed
    while(key == 'n')              // Wait untill a key is pressed
        key = Keypad_Scanner();   // Scan the keys again and again
    return key;                  //when key pressed then return its value
}

