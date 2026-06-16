#include "cm7_main.h"

void SysTick_Handler(void) {
    HAL_IncTick();
}

void USART2_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart2);
}

void HardFault_Handler(void) {
    error_handler();
}
