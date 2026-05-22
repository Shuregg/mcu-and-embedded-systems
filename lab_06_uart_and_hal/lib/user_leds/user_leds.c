#include "user_leds.h"
#include <stm32h7xx.h>

void led_enable_green();
void led_enable_yellow();
void led_enable_red();

void led_toggle_green();
void led_toggle_yellow();
void led_toggle_red();

void led_on_green();
void led_on_yellow();
void led_on_red();

void led_off_green();
void led_off_yellow();
void led_off_red();

void led_disable_green();
void led_disable_yellow();
void led_disable_red();

void led_enable(led_t led) {
    switch (led) {
        case led_green: {
            led_enable_green();
            break;
        }
        case led_yellow: {
            led_enable_yellow();
            break;
        }
        case led_red: {
            led_enable_red();
            break;
        }
        case led_all: {
            led_enable_green();
            led_enable_yellow();
            led_enable_red();
            break;
        }
        default: {
            break;
        }
    }
}

void led_toggle(led_t led) {
    switch (led) {
        case led_green: {
            led_toggle_green();
            break;
        }
        case led_yellow: {
            led_toggle_yellow();
            break;
        }
        case led_red: {
            led_toggle_red();
            break;
        }
        case led_all: {
            led_toggle_green();
            led_toggle_yellow();
            led_toggle_red();
            break;
        }
        default: {
            break;
        }
    }
}

void led_on(led_t led) {
    switch (led) {
        case led_green: {
            led_on_green();
            break;
        }
        case led_yellow: {
            led_on_yellow();
            break;
        }
        case led_red: {
            led_on_red();
            break;
        }
        case led_all: {
            led_on_green();
            led_on_yellow();
            led_on_red();
            break;
        }
        default: {
            break;
        }
    }
}

void led_off(led_t led) {
    switch (led) {
        case led_green: {
            led_off_green();
            break;
        }
        case led_yellow: {
            led_off_yellow();
            break;
        }
        case led_red: {
            led_off_red();
            break;
        }
        case led_all: {
            led_off_green();
            led_off_yellow();
            led_off_red();
            break;
        }
        default: {
            break;
        }
    }
}

void led_disable(led_t led) {
    switch (led) {
        case led_green: {
            led_disable_green();
            break;
        }
        case led_yellow: {
            led_disable_yellow();
            break;
        }
        case led_red: {
            led_disable_red();
            break;
        }
        case led_all: {
            led_disable_green();
            led_disable_yellow();
            led_disable_red();
            break;
        }
        default: {
            break;
        }
    }
}

void led_enable_green() {
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
    GPIOB->MODER &= ~GPIO_MODER_MODE0_Msk; // включаем режим "output" ...
    GPIOB->MODER |= GPIO_MODER_MODE0_0; // ... для pin 0 
}
void led_enable_yellow() {
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
    GPIOE->MODER &= ~GPIO_MODER_MODE1_Msk; // включаем режим "output" ...
    GPIOE->MODER |= GPIO_MODER_MODE1_0; // ... для pin 1
}
void led_enable_red() {
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
    GPIOB->MODER &= ~GPIO_MODER_MODE14_Msk; // включаем режим "output" ...
    GPIOB->MODER |= GPIO_MODER_MODE14_0; // ... для pin 14 
}


void led_toggle_green() {
    TOGGLE_BIT(GPIOB->ODR, GPIO_ODR_OD0_Msk)
}
void led_toggle_yellow() {
    TOGGLE_BIT(GPIOE->ODR, GPIO_ODR_OD1_Msk)
}
void led_toggle_red() {
    TOGGLE_BIT(GPIOB->ODR, GPIO_ODR_OD14_Msk)
}

void led_on_green() {
    GPIOB->ODR |= GPIO_ODR_OD0_Msk;
}
void led_on_yellow() {
    GPIOE->ODR |= GPIO_ODR_OD1_Msk;
}
void led_on_red() {
    GPIOB->ODR |= GPIO_ODR_OD14_Msk;
}

void led_off_green() {
    GPIOB->ODR &= ~GPIO_ODR_OD0_Msk;
}
void led_off_yellow() {
    GPIOE->ODR &= ~GPIO_ODR_OD1_Msk;
}
void led_off_red() {
    GPIOB->ODR &= ~GPIO_ODR_OD14_Msk;
}

void led_disable_green() {
    GPIOB->MODER &= ~GPIO_MODER_MODE0_Msk; // включаем режим "analog" ...
    GPIOB->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1; // ... для pin 0
}
void led_disable_yellow() {
    GPIOE->MODER &= ~GPIO_MODER_MODE1_Msk; // включаем режим "analog" ...
    GPIOE->MODER |= GPIO_MODER_MODE1_0 | GPIO_MODER_MODE1_1; // ... для pin 1
}
void led_disable_red() {
    GPIOB->MODER &= ~GPIO_MODER_MODE14_Msk; // включаем режим "analog" ...
    GPIOB->MODER |= GPIO_MODER_MODE14_0 | GPIO_MODER_MODE14_1; // ... для pin 0
}

