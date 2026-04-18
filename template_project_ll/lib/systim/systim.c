#include <stm32h7xx.h>
#include "systim.h"

static volatile uint32_t g_sys_counter_ms = 0;
static uint32_t g_ticks_in_mcs = 0;

void SysTick_Handler() {
    g_sys_counter_ms += 1;
}

uint32_t systim_current_ms() { 
    return  g_sys_counter_ms; 
};

void systim_init(uint32_t mcu_clock) {
    g_ticks_in_mcs = mcu_clock / 1000000U;
    // PM0253, раздел 4.4, стр 212.
    // TODO Запус SysTick
}
