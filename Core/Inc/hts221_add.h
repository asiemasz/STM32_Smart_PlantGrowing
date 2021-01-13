/*
 * hts221_add.h
 *
 *  Created on: Dec 6, 2020
 *      Author: pajcz
 */

#ifndef INC_HTS221_ADD_H_
#define INC_HTS221_ADD_H_

#include "hts221.h"
#include "main.h"
#include "iks01a2_env_sensors.h"
#include "lcd.h"
#include "sensors.h"

int32_t hts221_init();
int32_t hts221_read_temp(float *temp);
int32_t hts221_read_humid(float *humid);


#endif /* INC_HTS221_ADD_H_ */
