#include <stm32h7xx.h>
#include "systim.h"

static volatile uint32_t g_sys_counter_ms = 0;
static uint32_t g_ticks_in_us = 0;

void systim_SysTick_Handler() {
    g_sys_counter_ms += 1;
}
uint32_t systim_current_ms() {
    return g_sys_counter_ms;
};

void systim_init(uint32_t mcu_clock) {
    g_ticks_in_us = mcu_clock / 1000000U;
    // PM0253, раздел 4.4, стр 212.
    // TODO Запуск SysTick

    /* Configure the SysTick to have interrupt in 1ms time base */
    SysTick->LOAD  = (uint32_t)((mcu_clock / 1000U) - 1UL); /* set reload register */
    SysTick->VAL   = 0UL;                                   /* Load the SysTick Counter Value */
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                     SysTick_CTRL_ENABLE_Msk    |           /* Enable the Systick Timer */
                     SysTick_CTRL_TICKINT_Msk;

}

uint32_t systim_elapsed_ms(uint32_t from) {
    uint32_t elapsed = systim_current_ms() - from;
    return elapsed;
}

void systim_delay_ms(uint32_t ms) {
    #if 1
    uint32_t count = ms;

    // Clear the COUNTFLAG field
    uint32_t tmp =  SysTick->CTRL;
    (void)tmp; // Unused variable

    if (count != SYSTIM_MAX_DELAY)
        count++;

    while(count != 0U) {
        if((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
            count--;
    }

    #else
    uint32_t start_time_ms = systim_current_ms();
    while(systim_elapsed_ms(start_time_ms) < ms);
    #endif
}

void systim_delay_us(uint32_t us) {
    uint32_t count;
    if (us != SYSTIM_MAX_DELAY)
        us++;
    count = (g_ticks_in_us * us);
    while (count != 0U) {
        count--;
    }
}
