#include "stm32f4xx_hal.h"

void delay_us(uint32_t us) {
    TIM_HandleTypeDef htim;

    // ��ʼ����ʱ��
    htim.Instance = TIMx; // �滻Ϊ��Ҫʹ�õĶ�ʱ��
    htim.Init.Prescaler = SystemCoreClock / 1000000 - 1; // ���÷�Ƶֵ��ʵ��1΢��ļ���
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = us - 1; // ���ö�ʱ������
    HAL_TIM_Base_Init(&htim);

    // ������ʱ��
    HAL_TIM_Base_Start(&htim);

    // �ȴ���ʱ���������
    while (__HAL_TIM_GET_FLAG(&htim, TIM_FLAG_UPDATE) == RESET) {}

    // �رն�ʱ��
    HAL_TIM_Base_Stop(&htim);

    // �����ʱ����־λ
    __HAL_TIM_CLEAR_FLAG(&htim, TIM_FLAG_UPDATE);
}
