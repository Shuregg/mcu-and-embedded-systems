#include "cm7_main.h"

void SysTick_Handler(void) {
    HAL_IncTick();
}

void DMA1_Stream0_IRQHandler(void)
{
    HAL_DMA_IRQHandler(huart2.hdmarx);
}

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart2);
}

void HardFault_Handler(void) {
    error_handler();
}

// void HardFault_Handler(void)
// {
//     led_on(led_green);
//     while (1) {
//     }
// }