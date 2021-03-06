/**
 * @file inc/hts221_add.h
 * @brief Header for hts221_add.c file.
 */

#ifndef INC_HTS221_ADD_H_
#define INC_HTS221_ADD_H_

#include "hts221.h"
#include "main.h"
#include "iks01a2_env_sensors.h"
#include "lcd.h"
#include "sensors.h"

int32_t hts221_init();
int32_t hts221_readTemp(float *temp);
int32_t hts221_readHumid(float *humid);


#endif /* INC_HTS221_ADD_H_ */
