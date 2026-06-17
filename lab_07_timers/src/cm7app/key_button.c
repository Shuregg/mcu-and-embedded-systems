#include "key_button.h"
#include <stm32h7xx_hal.h>

void Key_Button_EXTI_Init()
{
    KEY_BUTTON_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = KEY_BUTTON_PIN;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    HAL_GPIO_Init(KEY_BUTTON_PORT, &GPIO_InitStruct);
    HAL_NVIC_SetPriority(KEY_BUTTON_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(KEY_BUTTON_IRQn);
}