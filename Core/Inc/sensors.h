/*
 * sensors.h
 *
 *  Created on: 5 lis 2020
 *      Author: pajcz
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "main.h"
#include "hts221_add.h"
#include <stdio.h>
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tim.h"
#include "eeprom.h"
#include "keyboard.h"

#define S_OK 0
#define S_LOWTEMP 1
#define S_HIGHTEMP 2
#define S_LOWHUM 3
#define S_HIGHHUM 4

typedef struct {
	float temp;
	float humid;
	char* soil;
}data;

extern data currentData;
extern data settingMin;
extern data settingMax;


void data_get(); //get all sensors data
char* convertMoisture(uint32_t adc_data);
void data_print(struct lcd_disp *disp);
void data_printAlert(int e, struct lcd_disp *disp);
uint8_t data_check();
void data_settingInit();
void data_settingEnter();
void data_settingSave();
void data_settingLoad();
void data_settingPrint();

#endif /* INC_SENSORS_H_ */
