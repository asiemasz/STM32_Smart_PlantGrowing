/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           src/main.c
  * @brief          Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 * Microcontroller project to help in plants growing at home. Device read temperature, air humidity and soil humidity from sensors, stores current readings in special structure and check if it fits limit values. Limit values can be set by user using keyboard and LCD screen. If any of readings is off limit values device alarms user.
 * \section Hardware
 *  -STM NUCLEO-F401RE: board
 *
 *  -x-NUCLEO-IKS102A: shield with environmental and motion sensors
 *
 * -Waveshare 9527: analog soil moisture sensor
 *
 * -membrane keyboard 4x3
 *
 * -LCD screen: HD44780 driver
 *
 * -buzzer with generator module
 *
 */
/** @addtogroup MAIN
  * @{
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "eeprom.h"
#include "hts221_add.h"
#include "lcd.h"
#include "buzzer.h"
#include "keyboard.h"
#include "sensors.h"
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t s; /*!< data from ADC input - DMA*/
uint8_t dataStatus; /*!< status of current data */
uint16_t VirtAddVarTab[NB_OF_VAR]; /*!< Table of virtual adresses for EEPROM emulation */
struct lcd_disp disp; /*!< LCD display struct used in program*/
uint8_t alertMode = 0; /*!< Alert mode: 1 - alert on; 0 - alert off */
uint8_t settingModeKb = 0,settingModeUart = 0;/*!< Setting mode: 1 - enable settings input mode */
uint16_t p; /*!< Variable storing data readed from EEPROM emulation */
volatile uint32_t delayCounter = 0; /*!< Counter of SysTick handler */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM11_Init();
  MX_I2C3_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_SYSTICK_Config(72000);
  hts221_init();

  data_settingInit();

  disp.addr = (0x27 << 1);
  disp.bl = true;
  lcd_init(&disp);
  sprintf((char *)disp.f_line, "PROGRAM ");
  sprintf((char *) disp.s_line,"START");
  lcd_display(&disp);
  HAL_Delay(500);
  lcd_clear(&disp);


  HAL_FLASH_Unlock();
  if(EE_Init() != HAL_OK){
	  Error_Handler();
  }

  if(EE_ReadVariable(MIN_HUM_ADDR, &p) == 0){
	  sprintf((char *)disp.f_line,"Loading settings");
	  sprintf((char *)disp.s_line,"from memory.");
	  lcd_display(&disp);
	  data_settingLoad();
	  HAL_Delay(3000);
	  lcd_clear(&disp);
	  data_settingPrint();
  }
  else{
	  data_settingInit();
	  sprintf((char *)disp.f_line,"Loading initial ");
	  sprintf((char *)disp.s_line,"settings.");
	  lcd_display(&disp);
	  HAL_Delay(1000);
	  lcd_clear(&disp);
	  data_settingPrint();
  }


  HAL_ADC_Start_DMA(&hadc1, &s, 1);

  HAL_TIM_Base_Start_IT(&htim11);
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if(settingModeKb == 0 && settingModeUart == 0)
		lcd_display(&disp);
	else if(settingModeKb == 1){
		data_settingEnter();
		data_settingSave();
		settingModeKb = 0;
	}
	else{
		usart_send_string("DZIALA");
		settingModeUart = 0;
	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 288;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
 * @brief Interrupts from TIM11 and TIM2 handlers.
 * 	TIM11 - check keyboard state
 * 			if no button pressed KB_STATE_IDLE
 * 			if button pressed for more than timer period KB_STATE_PRESSED
 * 			else KB_STATE_WAIT
 *
 * 			if "#" pressed activate settings mode
 * 	TIM2 - get data from sensors, check if data match requirements
 * 		if yes send data to LCD
 * 		if no alternately send data to LCD and send alarm message to LCD and activate alarm
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM11 ){
		uint8_t tempKey = kb_readKey();

		if(tempKey==0xFF)
		KB_STATE=KB_STATE_IDLE;
		else if(tempKey==KB_KEY)
		KB_STATE=KB_STATE_PRESSED;
		else{
		KB_STATE=KB_STATE_WAIT;
		KB_KEY=tempKey;
		}
		if(KB_STATE == KB_STATE_PRESSED && KB_KEY==KB_HASH)
			settingModeKb = 1;
		else if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)) {
			settingModeUart = 1;
			__HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_RXNE);
		}
	}


	if(htim->Instance == TIM2){
		if(settingModeKb || settingModeUart)
			return;
		data_get();
		dataStatus = data_check();
		if(dataStatus == S_OK){
			data_print(&disp);
		}
		else{
			if(alertMode == 1){
				data_printAlert((int)dataStatus,&disp);
				buzzerAlarm(1, VOLUME);
				alertMode = 0;
			}
			else if(alertMode == 0 ){
				data_print(&disp);
				alertMode = 1;
			}
		}

	}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	//lcd_display(0, 0, "Error occured!");
	HAL_Delay(5000);
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
