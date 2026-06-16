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

void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
    if (huart->Instance == USART2) {
        // USART5 (Sender): PD2 (AF8) -> USART5_RX; PC12 (AF8) -> USART5_TX;
        // Конфиграция тактирования
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_USART234578_CONFIG(RCC_USART234578CLKSOURCE_HSI);  // Kernel clock source

        // Конфигурация вывода TX
        GPIO_InitTypeDef gpio_init = {.Pin = GPIO_PIN_6,
                                      .Mode = GPIO_MODE_AF_PP,
                                      .Pull = GPIO_NOPULL,
                                      .Speed = GPIO_SPEED_FREQ_LOW,
                                      .Alternate = GPIO_AF7_USART2};
        HAL_GPIO_Init(GPIOD, &gpio_init);

        HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
}