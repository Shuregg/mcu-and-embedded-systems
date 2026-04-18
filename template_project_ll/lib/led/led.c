#include <led.h>
#include <stm32h7xx.h>

#ifndef TOGGLE_BIT
#define TOGGLE_BIT(REG, POS) ((REG) ^= (POS))
#endif

/******  Красный светодиод   ******************************* */

static void led_red_enable() {
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN);
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE14_Msk, GPIO_MODER_MODE14_0);
};
static void led_red_disable() {
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE14_Msk, GPIO_MODER_MODE14_0 | GPIO_MODER_MODE14_1);
};
static void led_red_toggle() {
    TOGGLE_BIT(GPIOB->ODR, GPIO_ODR_OD14);
};
static void led_red_on() {
    GPIOB->BSRR |= GPIO_BSRR_BS14;
}
static void led_red_off() {
    GPIOB->BSRR |= GPIO_BSRR_BR14;
}

/******  Желтый светодиод   ****************************** */

static void led_yellow_enable() {
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOEEN);
    MODIFY_REG(GPIOE->MODER, GPIO_MODER_MODE1_Msk, GPIO_MODER_MODE1_0);
};
static void led_yellow_disable() {
    MODIFY_REG(GPIOE->MODER, GPIO_MODER_MODE1_Msk, GPIO_MODER_MODE1_0 | GPIO_MODER_MODE1_1);
};
static void led_yellow_toggle() {
    TOGGLE_BIT(GPIOE->ODR, GPIO_ODR_OD1);
};
static void led_yellow_on() {
    GPIOE->BSRR |= GPIO_BSRR_BS1;
}
static void led_yellow_off() {
    GPIOE->BSRR |= GPIO_BSRR_BR1;
}

/******  Зеленый светодиод   ****************************** */

static void led_green_enable() {
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN);
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE0_Msk, GPIO_MODER_MODE0_0);
};
static void led_green_disable() {
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE0_Msk, GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1);
};
static void led_green_toggle() {
    TOGGLE_BIT(GPIOB->ODR, GPIO_ODR_OD0);
};
static void led_green_on() {
    GPIOB->BSRR |= GPIO_BSRR_BS0;
}
static void led_green_off() {
    GPIOB->BSRR |= GPIO_BSRR_BR0;
}

/******  Адаптер для функции с API на основе перечислений enum   *** */

#define LED_FUNC(SUFIX)           \
    void led_##SUFIX(led_t led) { \
        if (led & led_red) {      \
            led_red_##SUFIX();    \
        };                        \
        if (led & led_yellow) {   \
            led_yellow_##SUFIX(); \
        };                        \
        if (led & led_green) {    \
            led_green_##SUFIX();  \
        }                         \
    }

LED_FUNC(enable)
LED_FUNC(toggle)
LED_FUNC(on)
LED_FUNC(off)
LED_FUNC(disable)
