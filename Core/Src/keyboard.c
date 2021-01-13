/*
 * keyboard.c
 *
 *  Created on: 5 lis 2020
 *      Author: pajcz
 */

#include "keyboard.h"

uint8_t KB_STATE=KB_STATE_IDLE;
uint8_t KB_KEY = 0xFF;

const unsigned char kbMap[4][3]={{1, 2, 3},
{4, 5, 6},
{7, 8, 9},
{KB_STAR, 0 , KB_HASH}};
const uint16_t kbRows[4] = {KB_R1_Pin, KB_R2_Pin, KB_R3_Pin, KB_R4_Pin};
const uint16_t kbCols[3] = {KB_C1_Pin,KB_C2_Pin,KB_C3_Pin};

uint8_t kb_read_key(){
	uint8_t r,c;
	for(r=0;r<4;r++){
		HAL_GPIO_WritePin(KB_PORT, KB_R1_Pin|KB_R2_Pin|KB_R3_Pin|KB_R4_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(KB_PORT, kbRows[r], GPIO_PIN_RESET);
		for(c=0;c<3;c++){
			if((!HAL_GPIO_ReadPin(KB_PORT, kbCols[c]))){
				return kbMap[r][c];
			}
		}
	}
	return 0xFF; //nic nie wciśnięte
}

uint8_t kb_service(){
	while(KB_STATE==KB_STATE_IDLE || KB_STATE==KB_STATE_WAIT);
	if(KB_STATE==KB_STATE_PRESSED)
		return KB_KEY;
}

uint8_t kb_ascii(uint8_t x){
	if(x>=0 && x<=9)
		return 48+x;
	else if(x==10)
		return 42;
	else if(x==11)
		return 35;
	else return 0;
}

