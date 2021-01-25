/**
 * @file inc/keyboard.h
 * @brief Header for keyboard.c file. This file contains macros and enum type.
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "main.h"
#include "gpio.h"
#include "lcd.h"
#include "tim.h"

/**
 * @addtogroup KEYBOARD
 * @{
 */
/**
 * @brief defines keyboard pins port
 */
#define KB_PORT GPIOA

/**
 * @brief defines value of '*' key
 */
#define KB_STAR 10
/**
 * @brief defines value of '#' key
 */
#define KB_HASH 11

/**
 * Enum type describing current keyboard state
 */
enum KEYBOARD_STATE{
	KB_STATE_IDLE, /**< no key pressed */
	KB_STATE_PRESSED,/**< key pressed */
	KB_STATE_WAIT/**<waiting for stable key press */
};

/**
 * @}
 */

extern uint8_t KB_STATE;
extern uint8_t KB_KEY;


uint8_t kb_readKey();//read what key is pressed
uint8_t kb_ascii(uint8_t x);
uint8_t kb_service();//wait for pressed key

#endif /* INC_KEYBOARD_H_ */
