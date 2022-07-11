#include "led.h"

__weak void led_off(Led_Typdef *LedX)
{
	
}

__weak void led_blink_1hz(Led_Typdef *LedX)
{
	
}

__weak void led_blink_5hz(Led_Typdef *LedX)
{
	
}

__weak void led_blink_10hz(Led_Typdef *LedX)
{
	
}

void led_init(Led_Typdef *LedX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	LedX->GPIOx = GPIOx;
	LedX->GPIO_Pin = GPIO_Pin;
}

void led_handle(Led_Typdef *LedX)
{
	switch(LedX->led_state_current)
	{
		case LED_OFF:
			led_off(LedX);
			break;
		case LED_BLINK_1HZ:
			led_blink_1hz(LedX);
			break;
		case LED_BLINK_5HZ:
			led_blink_5hz(LedX);
			break;
		case LED_BLINK_10HZ:
			led_blink_10hz(LedX);
			break;
		
		default:
			break;
	}
}



