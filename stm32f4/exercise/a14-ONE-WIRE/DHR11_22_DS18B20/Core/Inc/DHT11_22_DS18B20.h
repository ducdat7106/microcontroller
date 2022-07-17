/*
 * DHT11.h
 *
 *  Created on: 5 Jan 2022
 *      Author: NGUYEN DUC DAT
 */

#include<stdio.h>
#include<stdint.h>
#include<stm32f4xx_hal.h>

//TIM_HandleTypeDef htim6;

void DHT11_Start (void);
int DHT11_Check_Response (void);
uint8_t DHT11_Read (void);

