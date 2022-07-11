#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

typedef struct
{
	uint8_t state_press;
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Button_Typdef;

void button_handle(Button_Typdef *ButtonX);
void button_init(Button_Typdef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


#endif




