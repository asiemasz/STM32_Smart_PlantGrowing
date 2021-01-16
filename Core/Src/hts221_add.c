/*
 * hts221_add.c
 *
 *  Created on: Dec 6, 2020
 *      Author: pajcz
 */

#include "hts221_add.h"



int32_t hts221_init(){
	int32_t status;
	status = IKS01A2_ENV_SENSOR_Init(IKS01A2_HTS221_0, ENV_TEMPERATURE | ENV_HUMIDITY);
	return status;
}

int32_t hts221_readTemp(float *temp){
	int32_t status;
	status = IKS01A2_ENV_SENSOR_GetValue(IKS01A2_HTS221_0, ENV_TEMPERATURE, temp);
	return status;
}
int32_t hts221_readHumid(float *hum){
	int32_t status;
	status = IKS01A2_ENV_SENSOR_GetValue(IKS01A2_HTS221_0, ENV_HUMIDITY, hum);
	return status;
}
