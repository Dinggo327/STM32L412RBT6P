#pragma once
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#define LD4_Pin GPIO_PIN_13
#define LD4_GPIO_Port GPIOB

#define RGB_LED_PIN GPIO_PIN_6
#define RGB_LED_PORT GPIOB

#define LED_COUNT 15 // ��������
#define RESET_DURATION_US 50 // �����źų���ʱ�䣬��λ΢��
#define HIGH_BIT_DURATION_US 10 // �ߵ�ƽλʱ�䣬��λ΢��
#define LOW_BIT_DURATION_US 5 // �͵�ƽλʱ�䣬��λ΢��
  /* USER CODE END Header */

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
	void Error_Handler(void);

	/* USER CODE BEGIN EFP */

	/* USER CODE END EFP */

	/* Private defines -----------------------------------------------------------*/
#define LD4_Pin GPIO_PIN_13
#define LD4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LD4_Pin GPIO_PIN_13
#define LD4_GPIO_Port GPIOB

#define RGB_LED_PIN GPIO_PIN_6
#define RGB_LED_PORT GPIOB
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
