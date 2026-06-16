#pragma once

#include "stm32h7xx_hal.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <led.h>
#include <vterm.h>

#define RX_LED led_green
#define ERR_LED led_red

#define HOKKU_BUF_SIZE 256

extern UART_HandleTypeDef huart2;

void error_handler();