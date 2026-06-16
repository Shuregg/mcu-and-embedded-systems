#include <stm32h7xx_hal.h>
/** Функция аварийного завершения - остановка программы в цикле мигания красным
светодиодом */
void error_freeze() __attribute__((__noreturn__));
/** Проверка статуса HAL, с аварийным завершением в случае ошибки */
void assert_hal_status(HAL_StatusTypeDef status);
