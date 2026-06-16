#include <stm32h7xx_hal.h>
#include "led.h"
#include "hal_helpers.h"
#include "error_state.h"

#include <vterm.h>
#include "error_handler.h"
#include "key_button.h"
#include "tim_mesure.h"
#include "tim_pulse.h"

#define VTERM_SPEED 115200

void TIMm_IRQHandler() { HAL_TIM_IRQHandler(&hTimMesure); }
void TIMm_DMA_IRQHandler(void) { HAL_DMA_IRQHandler(hTimMesure.hdma[TIMm_DMA_ID]); }