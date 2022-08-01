/* 
 * File:   HC_SR_04.h
 * Author: DAT PC
 *
 * Created on 27 January, 2022, 6:52 AM
 */

#ifndef HC_SR_04_H
#define	HC_SR_04_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include <xc.h>

    /*
     Using TIMER1
     */
    
    #define Echo PORTDbits.RD0      //INPUT PIN
    #define Trigger PORTDbits.RD1   //OUTPUT PIN

    #define Tris_Echo TRISDbits.TRISD0
    #define Tris_Trigger TRISDbits.TRISD1

    void HC_SR_04_Init();
    int HC_SR_04_Time_Taken();
    int HC_SR_04_Distance(int time_taken_value);

#ifdef	__cplusplus
}
#endif

#endif	/* HC_SR_04_H */

