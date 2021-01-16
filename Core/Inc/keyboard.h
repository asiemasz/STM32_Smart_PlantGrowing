/*
 * keyboard.h
 *
 *  Created on: 5 lis 2020
 *      Author: pajcz
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "main.h"
#include "gpio.h"
#include "lcd.h"
#include "tim.h"

#define KB_PORT GPIOA

#define KB_STAR 10
#define KB_HASH 11

enum{
	KB_STATE_IDLE,//nothing happens
	KB_STATE_PRESSED,//key pressed
	KB_STATE_WAIT//wait for stable key
};


extern uint8_t KB_STATE;
extern uint8_t KB_KEY;


uint8_t kb_readKey();//read what key is pressed
uint8_t kb_ascii(uint8_t x);
uint8_t kb_service();//wait for pressed key

#endif /* INC_KEYBOARD_H_ */
