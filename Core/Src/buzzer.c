/*
 * buzzer.c
 *
 *  Created on: 5 lis 2020
 *      Author: pajcz
 */

#include "buzzer.h"



void buzzerAlarm(uint8_t time,uint8_t power){
	htim3.Instance->CCR1 = power;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	delayCounter = time * 1000;
}
