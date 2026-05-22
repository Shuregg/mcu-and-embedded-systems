#include "cm4_main.h"

void HAL_MspInit(void) {
    led_enable(SIGNAL_LED);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == UART5) {
        // USART5 (Sender): PD2 (AF8) -> USART5_RX; PC12 (AF8) -> USART5_TX;
        // Конфигурация тактирования
        __HAL_RCC_UART5_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();
        __HAL_RCC_USART234578_CONFIG(RCC_USART234578CLKSOURCE_HSI); // Kernel clock source

        // Конфигурация вывода TX
        GPIO_InitTypeDef gpio_init = {
            .Pin = GPIO_PIN_12,
            .Mode = GPIO_MODE_AF_PP,
            .Pull = GPIO_PULLDOWN,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = GPIO_AF8_UART5
        };
        HAL_GPIO_Init(GPIOC, &gpio_init);

        // Конфигурация DMA2
        static DMA_HandleTypeDef hdma_tx = {0};
        hdma_tx.Instance = DMA2_Stream0;
        hdma_tx.Init.Request = DMA_REQUEST_UART5_TX;
        hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_tx.Init.Mode = DMA_CIRCULAR;
        hdma_tx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_tx) != HAL_OK) {
            error_handler();
        }
        __HAL_LINKDMA(huart, hdmatx, hdma_tx);
        HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
        HAL_NVIC_SetPriority(UART5_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(UART5_IRQn);
    }
}