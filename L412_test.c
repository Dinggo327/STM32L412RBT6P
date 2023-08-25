/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  /* USER CODE END Header */
  /* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// 定义一个结构体，用于存储RGB颜色值
typedef struct {
    uint8_t r; // 红色分量，0-255
    uint8_t g; // 绿色分量，0-255
    uint8_t b; // 蓝色分量，0-255
} rgb_t;

// 定义一个全局变量，用于存储灯条上每个LED的颜色值
rgb_t led_colors[LED_COUNT];
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//发送一个bit数据给DIN线
void send_bit(uint8_t bit) {
    if (bit) { // 如果bit为1，发送一个高电平脉冲
        HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); // 设置DIN线为高电平
        for (int i = 0; i < 7; i++) {} // 延时约0.35us
        HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // 设置DIN线为低电平
        for (int i = 0; i < 3; i++) {} // 延时约0.15us
    }
    else { // 如果bit为0，发送一个低电平脉冲
        HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); // 设置DIN线为高电平
        for (int i = 0; i < 3; i++) {} // 延时约0.15us
        HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // 设置DIN线为低电平
        for (int i = 0; i < 7; i++) {} // 延时约0.35us
    }
}

// 发送一个字节数据给DIN线
void send_byte(uint8_t byte) {
    for (int i = 0; i < 8; i++) { // 遍历字节中的每一位
        send_bit(byte & 0x80); // 发送最高位
        byte <<= 1; // 左移一位
    }
}

// 发送一个RGB颜色值给DIN线
void send_color(rgb_t color) {
    send_byte(LED_BRIGHTNESS); // 发送亮度值
    send_byte(color.b); // 发送蓝色分量
    send_byte(color.g); // 发送绿色分量
    send_byte(color.r); // 发送红色分量
}

// 更新灯条上的所有LED颜色
void update_leds() {
    for (int i = 0; i < LED_COUNT; i++) { // 遍历每个LED
        send_color(led_colors[i]); // 发送对应的颜色值
    }
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // 设置DIN线为低电平
    HAL_Delay(1); // 延时1ms，等待灯条刷新
}

// 生成彩虹色的颜色值
rgb_t rainbow_color(uint8_t pos)
{
    rgb_t color;
    pos = (pos + LED_COUNT) % LED_COUNT; // 限制pos在0-LED_COUNT之间
    if (pos < LED_COUNT / 6) { // 红-黄区间
        color.r = 255;
        color.g = pos * 255 / (LED_COUNT / 6);
        color.b = 0;
    }
    else if (pos < LED_COUNT / 3) { // 黄-绿区间
        color.r = 255 - (pos - LED_COUNT / 6) * 255 / (LED_COUNT / 6);
        color.g = 255;
        color.b = 0;
    }
    else if (pos < LED_COUNT / 2) { // 绿-青区间
        color.r = 0;
        color.g = 255;
        color.b = (pos - LED_COUNT / 3) * 255 / (LED_COUNT / 6);
    }
    else if (pos < LED_COUNT * 2 / 3) { // 青-蓝区间
        color.r = 0;
        color.g = 255 - (pos - LED_COUNT / 2) * 255 / (LED_COUNT / 6);
        color.b = 255;
    }
    else if (pos < LED_COUNT * 5 / 6) { // 蓝-紫区间
        color.r = (pos - LED_COUNT * 2 / 3) * 255 / (LED_COUNT / 6);
        color.g = 0;
        color.b = 255;
    }
    else { // 紫-红区间
        color.r = 255;
        color.g = 0;
        color.b = 255 - (pos - LED_COUNT * 5 / 6) * 255 / (LED_COUNT / 6);
    }
    return color;
}

//初始化灯条上的所有LED颜色为彩虹色
void init_leds() {
    for (int i = 0; i < LED_COUNT; i++) {//遍历每个LED
        led_colors[i] = rainbow_color(i);//生成对应的彩虹色值
    }
    update_leds();//更新灯条上的颜色
}

//旋转灯条上的所有LED颜色，实现循环效果
void rotate_leds() {
    rgb_t temp = led_colors[0];//保存第一个LED的颜色值
    for (int i = 0; i < LED_COUNT - 1; i++) {//遍历除了最后一个以外的每个LED
        led_colors[i] = led_colors[i + 1];//将后一个LED的颜色值赋给前一个LED
    }
    led_colors[LED_COUNT - 1] = temp;//将第一个LED的颜色值赋给最后一个LED
    update_leds();//更新灯条上的颜色
}

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
    MX_TIM2_Init();
    /* USER CODE BEGIN 2 */

    // 初始化灯条上的所有LED颜色为彩虹色
    init_leds();

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
         // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);

        rgb_t rainbow_color(uint8_t pos);
        rotate_leds();//旋转灯条上的所有LED颜色
        HAL_Delay(50);
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 4294967295;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */

    /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

      /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);

    /*Configure GPIO pin : PA15 */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
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
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
       /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
