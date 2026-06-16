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

#define DMA_RX_SIZE     1
#define HOKKU_MAX_SIZE  256
#define HOKKU_HISTORY   1

#define DMA_BUF_SIZE 256

uint8_t dma_buf[DMA_BUF_SIZE];


extern UART_HandleTypeDef huart2;

void error_handler(void);