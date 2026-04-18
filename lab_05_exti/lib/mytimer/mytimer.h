#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "systim.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************* Программные таймеры **************************** */
typedef struct MyTimer_Struct {
    uint32_t start_tick;
    uint32_t period_ms;
} MyTimer;

/** Создает и запускает таймер */
MyTimer mytimer_create(uint32_t period_ms);

uint32_t mytimer_get_tick_counter();

/** Перезапускает таймер (начать измерние заново) */
void mytimer_restart(MyTimer *timer);

/** Перезапуск и переустановка отслеживаемого периода */
void mytimer_reset(MyTimer *timer, uint32_t period);

/** Проверка, что с момента запуска таймера прошел заданный период */
bool mytimer_is_ready(MyTimer *timer);

/** Возвращает число миллисекунд, пройденных с момента запуска таймера */
uint32_t mytimer_elapsed_ms(MyTimer *timer);

#ifdef __cplusplus
}
#endif