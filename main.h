#pragma once

#define LD4_Pin GPIO_PIN_13
#define LD4_GPIO_Port GPIOB

#define RGB_LED_PIN GPIO_PIN_6
#define RGB_LED_PORT GPIOB

#define LED_COUNT 15 // 灯珠数量
#define RESET_DURATION_US 50 // 重置信号持续时间，单位微秒
#define HIGH_BIT_DURATION_US 10 // 高电平位时间，单位微秒
#define LOW_BIT_DURATION_US 5 // 低电平位时间，单位微秒
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" 
{
#endif

	
#include "stm32l4xx_hal.h"


	void Error_Handler(void);


#define LD4_Pin GPIO_PIN_13
#define LD4_GPIO_Port GPIOB


#define LD4_Pin GPIO_PIN_13
#define LD4_GPIO_Port GPIOB

#define RGB_LED_PIN GPIO_PIN_6
#define RGB_LED_PORT GPIOB


#ifdef __cplusplus
}
#endif

#endif 

