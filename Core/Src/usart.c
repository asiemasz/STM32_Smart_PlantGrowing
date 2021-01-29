/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/**
 * @file src/usart.c
 * @brief This file contains functions to comunicate with computer via UART.
 */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart2;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}
/**
 * @addtogroup UART_COMMUNICATION
 * @{
 */
/* USER CODE BEGIN 1 */
/**
 * @brief send a single char via UART
 * @param ch: char to send via UART
 * @retval - 0x00U: HAL_OK - data sent correctly
 * 		   - 0x01U: HAL_ERROR - error during UART transmition
 * 		   - 0x02U: HAL_BUSY - UART busy
 * 		   - 0x03U: HAL_TIMEOUT - UART transmition lasted too long
 */
HAL_StatusTypeDef usart_send_char(char ch){
	HAL_StatusTypeDef result = HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, USART_TIMEOUT);
	return result;
}
/**
 * @brief send a string via UART
 * @param s: string to send via UART
 * @retval - 0x00U: HAL_OK - data sent correctly
 * 		   - 0x01U: HAL_ERROR - error during UART transmition
 * 		   - 0x02U: HAL_BUSY - UART busy
 * 		   - 0x03U: HAL_TIMEOUT - UART transmition lasted too long
 */
HAL_StatusTypeDef usart_send_string(char *s){
	HAL_StatusTypeDef result = HAL_UART_Transmit(&huart2, (uint8_t*)s, strlen(s), USART_TIMEOUT);
	return result;
}
/**
 * @brief receive a char via UART
 * @param None.
 * @retval char sent from UART to device
 */
uint8_t usart_receive_char(){
	uint8_t ch;
	while(!__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE));
	HAL_UART_Receive(&huart2, (uint8_t*) &ch, 1, USART_TIMEOUT);
	return ch;
}
/**
 * @brief enter new settings using uart communication
 * @param None.
 * @retval None.1
 */
void usart_settingEnter(){
	char data[4];
	char buf[100];
	usart_send_string("Setting mode. Please enter data in format xx.x .\r\n");
	usart_send_string("Please enter minimum humidity: ");
	HAL_StatusTypeDef stat = HAL_UART_Receive(&huart2, (uint8_t*)data, 4, 10000);
	float x = strtof(data, NULL);
	usart_send_string("\r\n");
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
