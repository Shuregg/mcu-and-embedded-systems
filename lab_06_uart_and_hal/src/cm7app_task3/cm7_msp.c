#pragma once

#include "stm32h7xx_hal.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <led.h>
#include <vterm.h>

#define RX_LED  led_green
#define ERR_LED led_red

#define HOKKU_BUF_SIZE 256

extern UART_HandleTypeDef huart2;

void error_handler(void);

void HAL_MspInit(void) {
    led_enable(RX_LED);
    led_enable(ERR_LED);
    led_enable(led_yellow);
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();
        __HAL_RCC_USART234578_CONFIG(RCC_USART234578CLKSOURCE_HSI);

        GPIO_InitTypeDef gpio_init = {0};

        gpio_init.Pin = GPIO_PIN_6;
        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Pull = GPIO_NOPULL;
        gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_init.Alternate = GPIO_AF7_USART2;

        HAL_GPIO_Init(GPIOD, &gpio_init);

        static DMA_HandleTypeDef hdma_rx;

        hdma_rx.Instance = DMA1_Stream0;
        hdma_rx.Init.Request = DMA_REQUEST_USART2_RX;
        hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_rx.Init.Mode = DMA_NORMAL;
        hdma_rx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

        if (HAL_DMA_Init(&hdma_rx) != HAL_OK) { error_handler(); }

        __HAL_LINKDMA(huart, hdmarx, hdma_rx);

        HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 1,0);
        HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
        HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
}