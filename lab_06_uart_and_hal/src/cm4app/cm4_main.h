#pragma once
#include "stm32h7xx_hal.h"
#include <user_leds.h>
#define SIGNAL_LED led_red
extern UART_HandleTypeDef huart;
void error_handler();
