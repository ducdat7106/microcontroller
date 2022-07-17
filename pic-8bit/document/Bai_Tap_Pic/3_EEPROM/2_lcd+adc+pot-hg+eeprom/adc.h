/* 
 * File:   adc.h
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 8:03 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void ADC_Initialize();
unsigned int ADC_Read(unsigned char channel);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

