#include "myled.h"
#include <stm32h7xx.h>

void myled_enable() {
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN; // включаем тактирование GPIOE
    GPIOE->MODER &= ~GPIO_MODER_MODE1_Msk; // включаем режим "output" ...
    GPIOE->MODER |= GPIO_MODER_MODE1_0; // ... для pin 1
}

void myled_toggle() {
    TOGGLE_BIT(GPIOE->ODR, GPIO_ODR_OD1_Msk)
}

void myled_disable() {
    GPIOE->MODER &= ~GPIO_MODER_MODE1_Msk; // включаем режим "analog" ...
    GPIOE->MODER |= GPIO_MODER_MODE1_0 | GPIO_MODER_MODE1_1; // ... для pin 1
}