/*
 * lcd.h
 *
 *  Created on: Nov 2, 2020
 *      Author: Adam Siemasz
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#include "i2c.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define HI2C hi2c3

#define RS_PIN 0x01
#define RW_PIN 0x02
#define EN_PIN 0x04
#define BL_PIN 0x08

#define INIT_8BIT 0x30
#define INIT_4BIT 0x02

#define LCD_CLEAR 0x01

#define UNDERLINE_OFF_BLINK_OFF 0x0C
#define UNDERLINE_OFF_BLINK_ON 0x0D
#define UNDERLINE_ON_BLINK_OFF 0x0E
#define UNDERLINE_ON_BLINK_ON 0x0F

#define LINE_1 0x80
#define LINE_2 0xC0

struct lcd_disp {
	uint8_t addr;
	char f_line[17];
	char s_line[17];
	bool bl;
};

void lcd_init(struct lcd_disp * lcd);
void lcd_write(uint8_t addr, uint8_t data, uint8_t xpin);
void lcd_display(struct lcd_disp * lcd);
void lcd_clear(struct lcd_disp * lcd);


#endif /* INC_LCD_H_ */

