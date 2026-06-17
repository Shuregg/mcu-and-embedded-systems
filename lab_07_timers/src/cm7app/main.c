#include "main.h"
#include <stdio.h>
#include "tim_mesure.h"
uint32_t current_distance;

int main()
{
    printf("\r\nStart...\r\n");
    HAL_Init();
    Key_Button_EXTI_Init();
    Tim_Pulse_Init();
    Tim_Mesure_Init();
    Tim_Mesure_Start();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);

    printf("\r\nPress B1 to generate pulse on PC8 and mesure it on PE5\r\n");
    __NOP();
    while (1)
    {
        Tim_Pulse_Start();
        if (Tim_Mesure_Wait_Once(50))
        {
            uint32_t pulse_us = Tim_Mesure_GetDiff();
            uint32_t distance_cm = pulse_us / 58;

            if (distance_cm < 10)
            {
                led_on(led_red);
                led_off(led_yellow);
                led_off(led_green);
            }
            else if (distance_cm < 20)
            {
                led_off(led_red);
                led_on(led_yellow);
                led_off(led_green);
            }
            else
            {
                led_on(led_red);
                led_on(led_yellow);
                led_off(led_green);
            }

            current_distance = distance_cm;
        } 
    }
    /* 2 Hz */
    HAL_Delay(500);
    return 0;
}

/**** Функции обратного вызова библиотеки HAL *****************************************/
void HAL_MspInit()
{
    __enable_irq();
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
    led_enable(led_all);
    led_off(led_all);
    vterm_init(VTERM_SPEED);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY_BUTTON_PIN)
    {
        printf("Distance = %lu cm\r\n", current_distance);
    }
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &hTimPulse)
    {
        Tim_Pulse_Stop(hTimPulse);
    }
}
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim)
{
    (void)htim;
    error_freeze();
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim)
{
    Tim_Mesure_IC_Callback(htim);
}
