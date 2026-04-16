#include "mytimer.h"
#include <stm32h7xx.h>



MyTimer mytimer_create(uint32_t period_ms) {
    MyTimer t = {systim_current_ms(), period_ms};
    return t;
}

#if 0
void mytimer_init(uint32_t core_clock) {
    
}
#endif

void mytimer_restart(MyTimer *timer) {
    // TODO
    timer->start_tick = systim_current_ms();
}

void mytimer_reset(MyTimer *timer, uint32_t period) {
    // TODO
    if (period == 0U)
        period++;
    timer->period_ms  = period;
    mytimer_restart(timer);
}

bool mytimer_is_ready(MyTimer *timer) {
    // TODO
    bool is_ready = systim_elapsed_ms(timer->start_tick) >= timer->period_ms;
    return is_ready;
}

uint32_t mytimer_elapsed_ms(MyTimer *timer) { 
    // TODO
    return systim_elapsed_ms(timer->start_tick);
}