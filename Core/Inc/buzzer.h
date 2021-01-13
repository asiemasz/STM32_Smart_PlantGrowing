/*
 * buzzer.h
 *
 *  Created on: 5 lis 2020
 *      Author: pajcz
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"
#include "gpio.h"
#include "tim.h"

#define VOLUME 200
void buzzer_alarm(uint8_t time,uint8_t power);


#endif /* INC_BUZZER_H_ */
