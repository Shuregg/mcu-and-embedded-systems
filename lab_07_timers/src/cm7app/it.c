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

void TIMm_IRQHandler() { HAL_TIM_IRQHandler(&hTimMesure); }
void TIMm_DMA_IRQHandler(void) { HAL_DMA_IRQHandler(hTimMesure.hdma[TIMm_DMA_ID]); }