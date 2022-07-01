#include "hr04.h"

__weak void HCSR04_Complete_Callback(float kc)
{
	
}

void init_HCSR04(HC_SR04_Typdef *HCSR04x, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	HCSR04x->GPIOx = GPIOx;
	HCSR04x->GPIO_Pin = GPIO_Pin;
}

void HCSR04_Start(HC_SR04_Typdef *HCSR04x)
{
	//pin output mode
	HAL_GPIO_WritePin(HCSR04x->GPIOx, HCSR04x->GPIO_Pin, (GPIO_PinState)1);
	HAL_Delay(2);
	HAL_GPIO_WritePin(HCSR04x->GPIOx, HCSR04x->GPIO_Pin, (GPIO_PinState)0);
	HCSR04x->HCSR04_State = HCSR04_WAIT_RISING_STATE;	
}


void HC04_Handle( TIM_HandleTypeDef htim1, HC_SR04_Typdef *HCSR04x)
{
	if(HCSR04x->HCSR04_State == HCSR04_COMPLETE_STATE)
	{
		//tinh toan khoang cach
		float khoangCach = 0.017 * htim1.Instance->CNT;
		
		HCSR04_Complete_Callback(khoangCach);
		
		HCSR04x->HCSR04_State = HCSR04_IDLE_STATE;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
}




