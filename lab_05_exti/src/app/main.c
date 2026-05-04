#include "nuc745_utils.h"
#include <user_leds.h>
#include <stm32h7xx.h>
#include <stm32h7xx_ll_bus.h>
#include <stm32h7xx_ll_exti.h>
#include <stm32h7xx_ll_gpio.h>
#include <stm32h7xx_ll_system.h>
#include <stdio.h>
#include "systim.h"
#include "mytimer.h"
#include "vterm.h"

static uint32_t encoder_counter;
static MyTimer debounce_dt_timer;
static MyTimer debounce_sw_timer;

void SysTick_Handler() { systim_SysTick_Handler(); }

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

void encoder_KY_040_to_CN9_init() {
    // 1. Сконфигурировать пины ввода-вывода PE2, PE4, PE4, PE6 (CN9)
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);

#if 0
    LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_2, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_4, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_5, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);

    LL_GPIO_SetPinPull(GPIOE, LL_GPIO_PIN_4, LL_GPIO_PULL_DOWN);
    LL_GPIO_SetPinPull(GPIOE, LL_GPIO_PIN_5, LL_GPIO_PULL_DOWN);
    LL_GPIO_SetPinPull(GPIOE, LL_GPIO_PIN_6, LL_GPIO_PULL_DOWN);
#else
    LL_GPIO_InitTypeDef gpio_init = {
        .Pin = LL_GPIO_PIN_4 | LL_GPIO_PIN_5 | LL_GPIO_PIN_6,
        .Mode = LL_GPIO_MODE_INPUT,
        .Pull = LL_GPIO_PULL_UP
    };
    LL_GPIO_Init(GPIOE, &gpio_init);
#endif

    // 2.1. Включить тактирование банка регистров SYSCFG_EXTICR
    LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SYSCFG);

    // 2.2. Установить соответствие порта цифрового входа линии EXTI
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTE, LL_SYSCFG_EXTI_LINE4);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTE, LL_SYSCFG_EXTI_LINE5);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTE, LL_SYSCFG_EXTI_LINE6);

    // 3. задать триггеры для срабатывания прерывания

    // SW (encoder button)
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_4);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_4);
    // DT (ecnoder A)
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_5);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_5);
#ifdef USE_ENC_B
    // CLK (encoder B)
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_6);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_6);
#endif

    // 4. Включить генерацию сигнала прерывания
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_4); // SW
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_5); // DT
#ifdef USE_ENC_B
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_6); // CLK
#endif

    // 5. Сбросить бит ожидания прерывания для указанной линии
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
#ifdef USE_ENC_B
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
#endif

    // 6. Разрешить прерывание соответствующей линии EXTI
    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);

    NVIC_SetPriority(EXTI4_IRQn, 1);
    NVIC_SetPriority(EXTI9_5_IRQn, 1);
}

void EXTI4_IRQHandler(void) {
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_4)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);

        mytimer_restart(&debounce_dt_timer);
        while(!mytimer_is_ready(&debounce_dt_timer));

        if (!LL_GPIO_IsInputPinSet(GPIOE, LL_GPIO_PIN_4)) {
            encoder_counter = 0;
            printf("\n\rCounter reset to 0\n");
        }
    }
}

void EXTI9_5_IRQHandler(void) {
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_5)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);

        mytimer_restart(&debounce_dt_timer);
        while(!mytimer_is_ready(&debounce_dt_timer));

        uint32_t dt_val = LL_GPIO_IsInputPinSet(GPIOE, LL_GPIO_PIN_5);
        uint32_t clk_val = LL_GPIO_IsInputPinSet(GPIOE, LL_GPIO_PIN_6);
        if (dt_val != clk_val) {
            encoder_counter++;  // Clockwise operation
            printf("\n\rCounter (+): %ld\n", encoder_counter);

            led_toggle(led_green);
        } else {
            encoder_counter--;  // Counter-clockwise operation
            led_toggle(led_red);
            printf("\n\rCounter: %ld\n", encoder_counter);
        }
    }
}

void encoder_debounce_timers_init() {
    debounce_dt_timer = mytimer_create(100);
    debounce_sw_timer  = mytimer_create(100);
}

int main() {
    vterm_init(115200);
    systim_init(SystemCoreClock);
    encoder_debounce_timers_init();
    encoder_KY_040_to_CN9_init();
    wait_for_blue_button_release(); // защита от мгновенного сна после сброса
    led_enable(led_all);
    led_toggle(led_green);
    blue_button_init();
    while (1) {
        __WFI(); // режим процессора "Сон" до поступления прерывания
    }
    return 0;
}