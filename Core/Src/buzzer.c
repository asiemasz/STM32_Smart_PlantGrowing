/*
 * buzzer.c
 *
 *  Created on: 5 lis 2020
 *      Author: pajcz
 */

#include "buzzer.h"



void buzzer_alarm(uint8_t time,uint8_t power){
	htim3.Instance->CCR1 = power;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	delay_counter = time * 1000;
}
