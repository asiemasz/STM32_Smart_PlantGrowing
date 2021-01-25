/**
 * @file inc/buzzer.h
 * @brief Header for buzzer.c file. This file contains the function prototype.
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"
#include "gpio.h"
#include "tim.h"


/**
 * @addtogroup BUZZER
 * @{
 */
/**
 * @brief defines alarm volume
 */
#define VOLUME 200
/**
 *@}
 */
void buzzerAlarm(uint8_t time,uint8_t power);


#endif /* INC_BUZZER_H_ */
