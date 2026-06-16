#include "error_handler.h"
#include "hal_helpers.h"
#include "stm32h7xx_ll_utils.h"
#include <led.h>
#include <stdio.h>
#include <vterm.h>

void error_freeze()
{
    if (CoreDebug->DHCSR & 1)
        __BKPT(); // Если выолняется отладка, то прерываемся здесь
    led_enable(led_red);
    while (1)
    {
        led_toggle(led_red);
        LL_mDelay(250);
    }
}
void assert_hal_status(HAL_StatusTypeDef status)
{
    if (status != HAL_OK)
    {
        printf("\n\rERROR: %s", hal_status_to_string(status));
        error_freeze();
    }
}
/** Функция для обработки assert() из стандартной библиотеки */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
    printf("\r\nAssertrion \"%s\" failed in %s at %s:%d", failedexpr, func, file, line);
    error_freeze();
}
