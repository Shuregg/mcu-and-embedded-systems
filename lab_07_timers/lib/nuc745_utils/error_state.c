#include "error_state.h"
#include <led.h>
#include <stdio.h>
#include "stm32h7xx_ll_utils.h"

void error_state(const char* msg) {
    if (CoreDebug->DHCSR & 1)
        __BKPT();  // Если выолняется отладка, то прерываемся здесь
    if (msg) {
        puts(msg);
    }
    led_enable(led_red);
    LL_Init1msTick(SystemCoreClock);
    while (1) {
        led_toggle(led_red);
        LL_mDelay(250);
    }
}
