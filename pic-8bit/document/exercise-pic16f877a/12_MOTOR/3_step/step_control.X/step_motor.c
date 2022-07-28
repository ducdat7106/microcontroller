#include "step_motor.h"

void delay_ms(unsigned int value){
    for(int i=0; i<value; i++){
        __delay_ms(1);
    }
}

void Step_Motor_Init(){     
    //TRISD = 0xF0;       //all  tall pin PORTD pins are output
    TRIS_IN1=0;
    TRIS_IN2=0;
    TRIS_IN3=0;
    TRIS_IN4=0;
    
    IN1=IN2=IN3=IN4=0;
}

/*
Steps	A	B	C	D
    1   1	0	0	0
    2   0	1	0	0
    3   0	0	1	0
    4   0	0	0	1
 */
void Wave_Drive_Mode(char mode1, unsigned int delay){
    //mode = 1 = forward ; mode = 0 = reverse
    if(mode1 == 1){
        IN1=1; IN2=0; IN3=0; IN4=0; delay_ms(delay);
        IN1=0; IN2=1; IN3=0; IN4=0; delay_ms(delay);
        IN1=0; IN2=0; IN3=1; IN4=0; delay_ms(delay);
        IN1=0; IN2=0; IN3=0; IN4=1; delay_ms(delay);
    } else if(mode1 == 0){
        IN1=0; IN2=0; IN3=0; IN4=1; delay_ms(delay);
        IN1=0; IN2=0; IN3=1; IN4=0; delay_ms(delay);
        IN1=0; IN2=1; IN3=0; IN4=0; delay_ms(delay);
        IN1=1; IN2=0; IN3=0; IN4=0; delay_ms(delay);
    }
}


/*
 Steps	A	B	C	D
    1	1	1	0	0
    2	0	1	1	0
    3	0	0	1	1
    4	1	0	0	1
 */
void Full_Drive_Mode(char mode1, unsigned int delay){
    //mode = 1 = forward ; mode = 0 = reverse
    if(mode1 == 1){
        IN1=1; IN2=1; IN3=0; IN4=0; delay_ms(delay);
        IN1=0; IN2=1; IN3=1; IN4=0; delay_ms(delay);
        IN1=0; IN2=0; IN3=1; IN4=1; delay_ms(delay);
        IN1=1; IN2=0; IN3=0; IN4=1; delay_ms(delay);
    } else if(mode1 == 0){
        IN1=1; IN2=0; IN3=0; IN4=1; delay_ms(delay);
        IN1=0; IN2=0; IN3=1; IN4=1; delay_ms(delay);
        IN1=0; IN2=1; IN3=1; IN4=0; delay_ms(delay);
        IN1=1; IN2=1; IN3=0; IN4=0; delay_ms(delay);
    }
}


/*
 Steps	A	B	C	D
    1	1	0	0	0
    2	1	1	0	0
    3	0	1	0	0
    4	0	1	1	0
    5	0	0	1	0
    6	0	0	1	1
    7	0	0	0	1
    8	1	0	0	1
 */
void Half_Drive_Mode(char mode1, unsigned int delay){
    //mode = 1 = forward ; mode = 0 = reverse
    if(mode1 == 1){
    
        IN1=1; IN2=0; IN3=0; IN4=0;  delay_ms(delay);
        IN1=1; IN2=1; IN3=0; IN4=0;  delay_ms(delay);
        IN1=0; IN2=1; IN3=0; IN4=0;  delay_ms(delay);
        IN1=0; IN2=1; IN3=1; IN4=0;  delay_ms(delay);
        IN1=0; IN2=0; IN3=1; IN4=0;  delay_ms(delay);
        IN1=0; IN2=0; IN3=1; IN4=1;  delay_ms(delay);
        IN1=0; IN2=0; IN3=0; IN4=1;  delay_ms(delay);
        IN1=1; IN2=0; IN3=0; IN4=1;  delay_ms(delay);
    } else if(mode1 == 0){
        IN1=1; IN2=0; IN3=0; IN4=1;  delay_ms(delay);
        IN1=0; IN2=0; IN3=0; IN4=1;  delay_ms(delay);
        IN1=0; IN2=1; IN3=1; IN4=0;  delay_ms(delay);
        IN1=0; IN2=1; IN3=0; IN4=0;  delay_ms(delay);
        IN1=1; IN2=1; IN3=0; IN4=0;  delay_ms(delay);
        IN1=1; IN2=0; IN3=0; IN4=0;  delay_ms(delay);    
    }
}
