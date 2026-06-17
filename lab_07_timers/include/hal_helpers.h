#pragma once
#include "stm32h7xx_hal.h"

#if !defined (CASE) && !defined(DEFAULT)
#define CASE(VAL) case VAL: return #VAL
#define DEFUALT() default: "UNKNOWN"

static inline const char *hal_status_to_string(HAL_StatusTypeDef status) {
  switch (status) {
    CASE(HAL_OK);
    CASE(HAL_TIMEOUT);
    CASE(HAL_BUSY);
    CASE(HAL_ERROR);
    DEFUALT();
  }
}

static inline const char *hal_uart_state_to_string(HAL_UART_StateTypeDef state) {
  switch (state) {
    CASE(HAL_UART_STATE_RESET);
    CASE(HAL_UART_STATE_READY);
    CASE(HAL_UART_STATE_BUSY);
    CASE(HAL_UART_STATE_BUSY_TX);
    CASE(HAL_UART_STATE_BUSY_RX);
    CASE(HAL_UART_STATE_BUSY_TX_RX);
    CASE(HAL_UART_STATE_TIMEOUT);
    CASE(HAL_UART_STATE_ERROR);
    DEFUALT();
  };
};

static inline const char *hal_uart_error_to_string(uint32_t error) {
  switch (error) {
    CASE(HAL_UART_ERROR_NONE);
    CASE(HAL_UART_ERROR_PE);
    CASE(HAL_UART_ERROR_NE);
    CASE(HAL_UART_ERROR_FE);
    CASE(HAL_UART_ERROR_ORE);
    CASE(HAL_UART_ERROR_DMA);
    CASE(HAL_UART_ERROR_RTO);
    DEFUALT();
  }
}
#undef CASE
#undef DEFAULT
#endif
