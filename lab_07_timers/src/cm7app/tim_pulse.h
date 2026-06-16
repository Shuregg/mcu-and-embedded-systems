#pragma once
#include <stm32h7xx_hal.h>
#define TIMp TIM3
#define TIMp_CHANNEL TIM_CHANNEL_3
#define TIMp_PRESCALER (64000-1) /* 1 КГц */
#define TIMp_PERIOD (3000 -1) /* UE каждые 3 c */
#define TIMp_CLK_ENABLE __HAL_RCC_TIM3_CLK_ENABLE
#define TIMp_IRQn TIM3_IRQn
#define TIMp_IRQHandler TIM3_IRQHandler
// Вывод PB0 - зеленый светодиод
#define TIMp_CH_PORT GPIOB
#define TIMp_CH_PIN GPIO_PIN_0
#define TIMp_CH_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define TIMp_CH_GPIO_AF GPIO_AF2_TIM3
// Дополнительный Вывод PC8
#define TIMp_ECH_PORT GPIOC
#define TIMp_ECH_PIN GPIO_PIN_8
#define TIMp_ECH_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define TIMp_ECH_GPIO_AF GPIO_AF2_TIM3
extern TIM_HandleTypeDef hTimPulse;
/** Инициализация таймера для ШИМ генерации в режиме IT*/
void Tim_Pulse_Init();
/** Запуск таймера */
void Tim_Pulse_Start();
/** Остановка таймера */
void Tim_Pulse_Stop();
/** Деинциализация таймера */
void Tim_Pulse_Disable();
