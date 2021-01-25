/**
 * @file inc/sensors.h
 * @brief Header for sensors.c file. Contains macros defining data state and structure for containing data.
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

/**
 * @addtogroup SENSORS_DATA_MANAGE
 * @{
 */
/**
 * @brief all data meet up with requirements
 */
#define S_OK 0
/**
 * @brief temperature too low!
 */
#define S_LOWTEMP 1
/**
 * @brief temperature too high!
 */
#define S_HIGHTEMP 2
/**
 * @brief air humidity too low!
 */
#define S_LOWHUM 3
/**
 * @brief air humidity too high!
 */
#define S_HIGHHUM 4
/**
 * \struct
 */
/**
 * @brief contains set of data from sensors
 */
typedef struct {
	float temp;
	float humid;
	char* soil;
}data;
/**
 * @}
 */

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
