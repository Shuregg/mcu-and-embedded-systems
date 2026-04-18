#include "stm32h7xx.h"
#include "nuc745_utils.h"
#include "led.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_gpio.h"

void wait_for_blue_button_release(){
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
    LL_GPIO_InitTypeDef but_pin_init_struct;
    LL_GPIO_StructInit(&but_pin_init_struct); // значения по умолчанию
    but_pin_init_struct.Mode = LL_GPIO_MODE_INPUT;
    but_pin_init_struct.Pin = LL_GPIO_PIN_13;
    LL_GPIO_Init(GPIOC, &but_pin_init_struct);
    while (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13)){
        led_enable(led_all);
        led_on(led_all);  
    };
    led_off(led_all);
    led_disable(led_all);
    LL_GPIO_DeInit(GPIOC);
}
