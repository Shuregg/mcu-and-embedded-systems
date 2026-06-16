#include "main.h"
void SysTick_Handler() { HAL_IncTick(); }
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}
void TIMp_IRQHandler()
{
    HAL_TIM_IRQHandler(&hTimPulse);
}
