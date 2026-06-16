#include "cm4_main.h"

void SysTick_Handler(void) {
    HAL_IncTick();
}

void DMA2_Stream0_IRQHandler(void) {
    HAL_DMA_IRQHandler(huart.hdmatx);
}

void USART5_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart);
}

void HardFault_Handler() {
    error_handler();
}