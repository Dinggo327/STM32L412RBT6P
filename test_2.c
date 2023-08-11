#include "main.h"
#include "tim.h"
#include "gpio.h"

#include <cstdint>

typedef struct
{
	uint8_t r, g, b;
}
WS2812_Color;

WS2812_Color ledColors[LED_COUNT];

void SystemClock_Config(void);

void sendColorDMA(uint32_t colorBits);
void sendResetSignal();

int main(void)
{
	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_TIM2_Init();

	while (1)
	{

		for (int i = 0; i < LED_COUNT; i++)
		{
			uint32_t colorBits = 0;  // 初始化一个32位的数据变量，用来构建颜色数据

			for (int j = 7; j >= 0; j--)
			{
				uint8_t bit = (ledColors[i].g >> j) & 0x01;  //获取当前位的值（0或1），用于构建颜色数据
				colorBits <<= 1;  //左移一位，为下一位的数据腾出位置
				if (bit)
				{
					colorBits |= 0x01;
				}// 如果当前位是1，设置colorBits的最低位为1
			}

			for (int j = 7; j >= 0; j--)
			{
				uint8_t bit = (ledColors[i].r >> j) & 0x01;
				colorBits <<= 1;
				if (bit)
				{
					colorBits |= 0x01;
				}
			}

			for (int j = 7; j >= 0; j--)
			{
				uint8_t bit = (ledColors[i].b >> j) & 0x01;
				colorBits <<= 1;
				if (bit)
				{
					colorBits |= 0x01;
				}
			}

			sendColorDMA(colorBits);
		}

		sendResetSignal();
		HAL_Delay(1000);

	}
}
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

void sendResetSignal()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_Delay(RESET_DURATION_US);
}
void sendColorDMA(uint32_t colorBits)
{
	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);

	__HAL_TIM_SET_AUTORELOAD(&htim2, colorBits);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, colorBits >> 1);

	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, &colorBits, 1);
}


void Error_Handler(void)
{

	__disable_irq();
	while (1)
	{
	}

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

}
#endif 





























