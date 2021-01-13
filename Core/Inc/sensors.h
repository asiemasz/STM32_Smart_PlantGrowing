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

extern data current_data;
extern data setting_min;
extern data setting_max;


void get_data(); //get all sensors data
void set_point();//set minimum/maximum temperature,humidity,soil humidity
char* convert_moisture(uint32_t adc_data);
void print_data(struct lcd_disp *disp);
void print_alert(int e, struct lcd_disp *disp);
uint8_t check_data();
void data_setting_init();
void data_setting_enter();
void data_setting_save();
void data_setting_load();
void data_setting_print();

#endif /* INC_SENSORS_H_ */
