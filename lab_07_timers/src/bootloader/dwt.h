#pragma GCC push_options
#pragma GCC optimize("O3")

#include <stm32h7xx.h>

static inline void dwt_enable() {
    SET_BIT(CoreDebug->DEMCR, CoreDebug_DEMCR_TRCENA_Msk);
    SET_BIT(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
    DWT->CYCCNT = 0;
}
static inline void dwt_disable() {
    CLEAR_BIT(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
}
static inline void dwt_start() {
    DWT->CYCCNT = 0;
}
static inline uint32_t dwt_get_mcs() {
    return DWT->CYCCNT / (SystemCoreClock / 1000000);
}

static inline void dwt_delay_mcs(int mcs) {
    uint32_t cycles = SystemCoreClock / 1000000 * mcs;
    DWT->CYCCNT = 0;
    while (DWT->CYCCNT < cycles)
        __asm("nop");
}
#pragma GCC pop_options