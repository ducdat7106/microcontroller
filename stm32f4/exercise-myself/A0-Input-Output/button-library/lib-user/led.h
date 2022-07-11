#ifndef LED_H
#define LED_H

#include "main.h"
typedef enum
{
	LED_OFF,
	LED_BLINK_1HZ,
	LED_BLINK_5HZ,
	LED_BLINK_10HZ
}Led_Status;

typedef struct
{
	Led_Status led_state_current;
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;	
}Led_Typdef;


void led_init(Led_Typdef *LedX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void led_handle(Led_Typdef *LedX);

#endif



