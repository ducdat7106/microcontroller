#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>

#define button HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)

#define led1_on  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)
#define led1_off HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET)

#define led2_on HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET)
#define led2_off HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET)

void Bink_Led(int value, char ch[]);
