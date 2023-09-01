#include "stm32f4xx_hal.h"

void delay_us(uint32_t us) {
    TIM_HandleTypeDef htim;

    // 初始化定时器
    htim.Instance = TIMx; // 替换为您要使用的定时器
    htim.Init.Prescaler = SystemCoreClock / 1000000 - 1; // 设置分频值以实现1微秒的计数
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = us - 1; // 设置定时器周期
    HAL_TIM_Base_Init(&htim);

    // 启动定时器
    HAL_TIM_Base_Start(&htim);

    // 等待定时器计数完成
    while (__HAL_TIM_GET_FLAG(&htim, TIM_FLAG_UPDATE) == RESET) {}

    // 关闭定时器
    HAL_TIM_Base_Stop(&htim);

    // 清除定时器标志位
    __HAL_TIM_CLEAR_FLAG(&htim, TIM_FLAG_UPDATE);
}
