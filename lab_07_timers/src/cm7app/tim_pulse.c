#include "tim_pulse.h"
#include "error_handler.h"
TIM_HandleTypeDef hTimPulse;
void Tim_Pulse_Init()
{
    // Инициализация таймера в режим ШИМ
    hTimPulse.Instance = TIMp;
    hTimPulse.Init.Period = TIMp_PERIOD;
    hTimPulse.Init.Prescaler = TIMp_PRESCALER;
    hTimPulse.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    hTimPulse.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTimPulse.Init.RepetitionCounter = 0;
    HAL_StatusTypeDef status = HAL_TIM_PWM_Init(&hTimPulse);
    assert_hal_status(status);
    // Инциализация выхода таймера
    TIM_OC_InitTypeDef sOCConfig = {0};
    sOCConfig.OCMode = TIM_OCMODE_PWM2;
    sOCConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    sOCConfig.Pulse = 0; // коэфициент заполнения шим D = 100%
    sOCConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
    sOCConfig.OCNPolarity = TIM_OCNPOLARITY_LOW;
    sOCConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    status = HAL_TIM_PWM_ConfigChannel(&hTimPulse, &sOCConfig, TIMp_CHANNEL);
    assert_hal_status(status);
}
void Tim_Pulse_Start()
{
    if (HAL_TIM_GetChannelState(&hTimPulse, TIMp_CHANNEL) == HAL_TIM_CHANNEL_STATE_READY)
    {
        HAL_StatusTypeDef status = HAL_TIM_PWM_Start_IT(&hTimPulse, TIMp_CHANNEL);
        assert_hal_status(status);
    }
}
void Tim_Pulse_Stop()
{
    HAL_StatusTypeDef status = HAL_TIM_PWM_Stop_IT(&hTimPulse, TIMp_CHANNEL);
    assert_hal_status(status);
}
void Tim_Pulse_Disable()
{
    HAL_TIM_PWM_DeInit(&hTimPulse);
}
/**** Функции обратного вызова библиотеки HAL *****************************************/
/** Переопредленные ниже функцию обрабатывают любые PWM таймеры и обычно помещается в
отдельный *msp.c
* файл В нашей программе толко один PWM таймер, поэтому мы поместили эти функции здесь.
*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim == &hTimPulse)
    {
        // Включаем тактирование
        TIMp_CLK_ENABLE();
        TIMp_CH_CLK_ENABLE();
        TIMp_ECH_CLK_ENABLE();
        // Вывод на светодиод
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = TIMp_CH_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
        GPIO_InitStruct.Alternate = TIMp_CH_GPIO_AF;
        HAL_GPIO_Init(TIMp_CH_PORT, &GPIO_InitStruct);
        // Вывод PC8
        GPIO_InitStruct.Pin = TIMp_ECH_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
        GPIO_InitStruct.Alternate = TIMp_ECH_GPIO_AF;
        HAL_GPIO_Init(TIMp_ECH_PORT, &GPIO_InitStruct);
        // Включаем прерывания
        HAL_NVIC_SetPriority(TIMp_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(TIMp_IRQn);
    }
}
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
{
    if (htim == &hTimPulse)
    {
        HAL_GPIO_DeInit(TIMp_CH_PORT, TIMp_CH_PIN);
        HAL_GPIO_DeInit(TIMp_ECH_PORT, TIMp_ECH_PIN);
    }
}