#pragma once
#include "stm32h7xx_hal.h"
// Конфигурация таймера
#define TIMm TIM15
#define TIMm_CHANNEL TIM_CHANNEL_1
#define TIMm_PRESCALER (64000 - 1) // 1 КГц
#define TIMm_PERIOD (65535)
#define TIMm_CLK_ENABLE __HAL_RCC_TIM15_CLK_ENABLE
#define TIMm_IRQn TIM15_IRQn
#define TIMm_IRQHandler TIM15_IRQHandler
// Конфигурация DMA
#define TIMm_DMAx DMA2
#define TIMm_DMA_STREAM DMA2_Stream1
#define TIMm_DMA_CLK_ENABLE __HAL_RCC_DMA2_CLK_ENABLE
#define TIMm_DMA_IRQn DMA2_Stream1_IRQn
#define TIMm_DMA_IRQHandler DMA2_Stream1_IRQHandler
#define TIMm_DMA_ID TIM_DMA_ID_CC1
#define TIMm_DMA_REQUEST DMA_REQUEST_TIM15_CH1
#define TIMm_DMA_ACTIVE_CHANNEL HAL_TIM_ACTIVE_CHANNEL_1
// Входной пин PA0
#define TIMm_CH_PORT GPIOE
#define TIMm_CH_PIN GPIO_PIN_5
#define TIMm_CH_CLK_ENABLE __HAL_RCC_GPIOE_CLK_ENABLE
#define TIMm_CH_GPIO_AF GPIO_AF4_TIM15
extern TIM_HandleTypeDef hTimMesure;
/** Инициализация таймера в режим Input Capture Compare */
void Tim_Mesure_Init();
/** Запуск таймера в режиме DMA */
void Tim_Mesure_Start();
/* Остановка таймера*/
void Tim_Mesure_Stop();
/* Функция обаботки, которую следует поместить в HAL_TIM_IC_CaptureCallback*/
void Tim_Mesure_IC_Callback(TIM_HandleTypeDef *htim);
/** Возваращает измеренное время в миллисекундах */
uint16_t Tim_Mesure_GetDiff();
/* Ожидание завершения измереиня пульса. Возвращает 1, если пульс был измерен
Повторный вызов, после успешнго измрения будет возвращать 0 */
int Tim_Mesure_Wait_Once(uint32_t timeout);
/** Деинциализация таймера */
void Tim_Mesure_Deinit();
