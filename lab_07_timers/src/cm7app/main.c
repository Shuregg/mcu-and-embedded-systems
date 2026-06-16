#include "main.h"
#include <stdio.h>

int main()
{
    printf("\r\nStart...\r\n");
    HAL_Init();
    Key_Button_EXTI_Init();
    Tim_Pulse_Init();
    Tim_Mesure_Init();
    Tim_Mesure_Start();
    printf("\r\nPress B1 to generate pulse on PC8 and mesure it on PE5\r\n");
    __NOP();
    while (1)
    {
        if (Tim_Mesure_Wait_Once(1000))
        {
            int time_ms = Tim_Mesure_GetDiff();
            printf("\r\nMesured Pulse Time = %d\r\n", time_ms);
        }
        else
        {
            printf("\r\nwaiting...");
        }
    }
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
        Tim_Pulse_Start();
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