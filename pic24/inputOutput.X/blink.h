/* 
 * File:   blink.h
 * Author: Nguyet
 *
 * Created on 25 May, 2022, 3:33 PM
 */

#ifndef BLINK_H
#define	BLINK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include "xc.h"
    
    void initPin();
    
    void blinkLed();


#ifdef	__cplusplus
}
#endif

#endif	/* BLINK_H */

