/*
 * lcd.c
 *
 *  Created on: Nov 2, 2020
 *      Author: Adam Siemasz
 */

#include "lcd.h"

void lcd_init(struct lcd_disp * lcd){
	uint8_t xpin = 0;
	if(lcd->bl)
		xpin = BL_PIN;
	HAL_Delay(40);
	lcd_write(lcd->addr, INIT_8BIT, xpin);
	HAL_Delay(5);
	lcd_write(lcd->addr, INIT_8BIT, xpin);
	HAL_Delay(1);
	lcd_write(lcd->addr, INIT_8BIT, xpin);
	HAL_Delay(10);
	lcd_write(lcd->addr, INIT_4BIT, xpin);
	HAL_Delay(10);

	lcd_write(lcd->addr,0x28,xpin); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_write(lcd->addr,0x08,xpin); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_clear(&disp);
	HAL_Delay(1);
	lcd_write(lcd->addr,0x06,xpin); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_write(lcd->addr, UNDERLINE_OFF_BLINK_OFF,xpin);

}

void lcd_write(uint8_t addr, uint8_t data, uint8_t xpin){
	uint8_t tx_data[4];

	tx_data[0] = (data & 0xF0) | EN_PIN | xpin;
	tx_data[1] = (data & 0xF0) | xpin;
	tx_data[2] = (data << 4) | EN_PIN | xpin;
	tx_data[3] = (data << 4) | xpin;
	HAL_I2C_Master_Transmit(&HI2C, addr, tx_data, 4, 100);

	HAL_Delay(5);
}

void lcd_display(struct lcd_disp * lcd){
	uint8_t xpin = 0 , i = 0;
	if(lcd->bl){
		xpin = BL_PIN;
	}

	lcd_write(lcd->addr, LINE_1, xpin);
	while(lcd->f_line[i])
	{
		lcd_write(lcd->addr,lcd->f_line[i], (xpin | RS_PIN));
		i++;
	}
	i = 0;
	lcd_write(lcd->addr, LINE_2, xpin);
	while(lcd->s_line[i])
		{
			lcd_write(lcd->addr,lcd->s_line[i], (xpin | RS_PIN));
			i++;
		}
}

void lcd_clear(struct lcd_disp * lcd){
	uint8_t xpin = 0;
	if(lcd->bl)
	{
		xpin = BL_PIN;
	}
	lcd_write(lcd->addr,LCD_CLEAR,xpin);

}
