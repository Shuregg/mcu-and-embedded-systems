#include "nuc745_utils.h"
#include <user_leds.h>
#include <stm32h7xx.h>
#include <stm32h7xx_ll_bus.h>
#include <stm32h7xx_ll_exti.h>
#include <stm32h7xx_ll_gpio.h>
#include <stm32h7xx_ll_system.h>
#include "mytimer.h"

#define USE_LL
/**
 * Конфигруация внешнего прерывания для кнопки B1
 * */

void blue_button_init() {
    // 1. Сконфигурировать пин ввода-вывода в режим входа.
#ifdef USE_LL
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_INPUT);
#else
    SET_BIT(RCC->AHB4ENR, RGCC_AHB4ENR_GPIOCEN);
    MODIFY_REG(GPIOC->MODER, PIO_MODER_MODE13, 0);
#endif

    // 2.1. Включить тактирование банка регистров SYSCFG_EXTICR
#ifdef USE_LL
    LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SYSCFG);
#else
    RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;
#endif
    // 2.2. Установить соответствие порта цифрового входа линии EXTI
#ifdef USE_LL
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);
#else
    MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk,
               SYSCFG_EXTICR4_EXTI13_PC);
#endif
    // 3. задать триггеры для срабатывания прерывания
#ifdef USE_LL
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_13);
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_13);
#else
    EXTI->RTSR1 |= EXTI_RTSR1_TR13; // тригер по нарастающему фронту
    EXTI->FTSR1 |= EXTI_FTSR1_TR13; // тригер по ниспадающему фронту
#endif
    // 4. Включить генерацию сигнала прерывания
#ifdef USE_LL
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_13);
#else
    EXTI->IMR1 |= EXTI_IMR1_IM13; // разрешаем сигнал активации прерывания
#endif
    // 5. Сбросить бит ожидания прерывания для указанной линии
#ifdef USE_LL
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
#else
    EXTI->PR1 = EXTI_PR1_PR13;
#endif
    // 6. Разрешить прерывание соответствующей линии EXTI
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/** * Проверка удержания кнопки B1
 * */
int blue_button_pressed() {
#ifdef USE_LL
    return LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13);
#else
    return GPIOC->IDR & GPIO_IDR_ID13;
#endif
}

/**
 * Обработка изменения сигнала кнопки B1
 * */
void blue_button_edge_handler() {
    if (blue_button_pressed())
        led_toggle(led_green);
    else
        led_toggle(led_yellow);
}

/**
 * ISR для прерывания по EXTI * */
void EXTI15_10_IRQHandler() {
#ifdef USE_LL
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
        blue_button_edge_handler();
    }
#else
    // a) проверить источник прерывания в регистре PR
    if (EXTI->PR1 & EXTI_PR1_PR13) {
        // б) сбросить флаг ожидания обработки в регистре
        EXTI->PR1 = EXTI_PR1_PR13;
        // в) выполнить операции для реализации задуманной логики PR
        blue_button_edge_handler();
    }
#endif
}

int main() {
    wait_for_blue_button_release(); // защита от мгновенного сна после сброса
    led_enable(led_all);
    led_toggle(led_green);
    blue_button_init();
    while (1) {
        __WFI(); // режим процессора "Сон" до поступления прерывания
    }
    return 0;
}