#include "button.h"

__weak void btn_press_callback(Button_Typdef *ButtonX)
{
	
}

void button_init(Button_Typdef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX->GPIOx = GPIOx;
	ButtonX->GPIO_Pin = GPIO_Pin;
}


void button_handle(Button_Typdef *ButtonX)
{
	uint8_t state_button = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
	if(state_button == 0)
	{
			ButtonX->state_press = 1;
	}
	
	if(state_button == 1 && ButtonX->state_press == 1)
	{
		ButtonX->state_press = 0;
		
		//do something
		btn_press_callback(ButtonX);		
	}
	
}


