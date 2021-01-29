/**
  * @file    src/buzzer.c
  * @brief   This file provides the buzzer handling using PWM function
*/


/** @addtogroup COMPONENTS
  * @{
  */
/** @addtogroup BUZZER
 * @{
 */
#include "buzzer.h"


/**
 * @brief Start buzzer alarm - start htim3 PWM Channel for the certain time
 * @param time: alarm time in seconds
 * @param power: power of alarm
 * 	This parameter can be one of values 0-1000 (the smaller value, the louder alarm sounds)
 * @retval none
 */
void buzzerAlarm(uint8_t time,uint8_t power){
	htim3.Instance->CCR1 = power;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	delayCounter = time * 1000;
}
