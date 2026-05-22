#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYSTIM_MAX_DELAY 0xFFFFFFFFU


// Инициализация 1-мс системного таймера
void systim_init(uint32_t mcu_clock);

// Возвращает счетчик миллисекунд с момента инициализации
uint32_t systim_current_ms();

// Возвращает кол-во милисекунд с момента FROM
// from - значение systim_current_ms() в момент FROM;
uint32_t systim_elapsed_ms(uint32_t from);

// Активное ожидание не менее ms милисекунд
void systim_delay_ms(uint32_t ms);

// Активное ожидание не менее us микросекунд
void systim_delay_mcs(uint32_t us);

void systim_SysTick_Handler();

#ifdef __cplusplus
}
#endif