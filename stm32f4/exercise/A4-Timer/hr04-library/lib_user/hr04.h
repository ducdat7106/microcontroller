#ifndef HC_SR04_H
#define HC_SR04_H

#include "main.h"

typedef enum
{
	HCSR04_IDLE_STATE,
	HCSR04_WAIT_RISING_STATE,
	HCSR04_WAIT_FALING_STATE,
	HCSR04_COMPLETE_STATE,
}HC_SR04_State;

typedef struct
{
	HC_SR04_State HCSR04_State;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}HC_SR04_Typdef;


void init_HCSR04(HC_SR04_Typdef *HCSR04x, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HCSR04_Start(HC_SR04_Typdef *HCSR04x);
void HCSR04_Handle();

#endif


