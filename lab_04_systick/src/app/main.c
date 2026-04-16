/**
 * Пример планировщика на базе программных таймеров
 */
#include "user_leds.h"
#include "mytimer.h"
#include "stm32h7xx.h"
#include "vterm.h"
#include <stdio.h>

#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_gpio.h"

void SysTick_Handler() { mytimer_SysTickHandler(); }

/*******************************************************************************
 * Программное меню *
 *******************************************************************************/

 #define NUM_COMMANDS 5
static void menu_show_tick() {
    uint32_t tick = mytimer_get_tick_counter();
    if (tick) {
        printf(u8"\nВремя работы %ld.%ld секунд", tick / 1000, tick % 1000);
    } else {
        printf(u8"\nСистеменый таймер не был настроен должным образом.");
    }
};

static void menu_show_title(void) {
    printf(
        u8"\r\n\n Меню приложения System clock is %ld "
        u8"MHz %s",
        SystemCoreClock / 1000000,
        u8"\n\r┌────────────┬────────────┬───────────┬────────────┬──────────┐"
        u8"\n\r│ 1:ShowTick │ 2:         │ 3:        │ 4:         │ 5: Reset │"
        u8"\n\r└────────────┴────────────┴───────────┴────────────┴──────────┘"
        u8"\n\r Выбор [1-6] > ");
};

typedef void (*handler_func_t)();
handler_func_t handlers[NUM_COMMANDS] = {menu_show_tick, NULL, NULL, NULL,
                                         NVIC_SystemReset};

/*******************************************************************************
 * Обработчик таймеров/задач *
 *******************************************************************************/

 led_t current_led = led_green;

typedef enum {
    FORWARD = 0,
    REVERSE = 1
} led_mode_e;

led_mode_e current_led_mode = FORWARD;

void hear_rate_handler(MyTimer *timer) {
    mytimer_restart(timer);
    led_toggle(current_led);
}
void change_led_handler(MyTimer *timer) {
    mytimer_restart(timer);
    led_off(current_led);
    current_led = current_led == led_green ? led_yellow : led_green;

    switch (current_led)
    {
    case led_green:
        current_led = (current_led_mode == FORWARD) ?  led_red : led_yellow;
        break;
    case led_yellow:
        current_led = (current_led_mode == FORWARD) ?  led_green : led_red;
        break;
    case led_red:
        current_led = (current_led_mode == FORWARD) ?  led_yellow : led_green; 
        break;
    }
}
void menu_handler(MyTimer *timer) {
    mytimer_restart(timer);
    uint8_t ch = vterm_keypressed();
    if (ch > 0) {
        putchar(ch); // echo
        uint8_t idx = ch - '1';
        if (idx < NUM_COMMANDS && handlers[idx]) {
            handlers[idx]();
        }
        menu_show_title();
    }
}

void led_mode_handler(MyTimer *timer) {
    mytimer_restart(timer);
    switch (current_led_mode) {
    case FORWARD:
        current_led_mode = REVERSE;
        break;
    case REVERSE:
        current_led_mode = FORWARD;
        break;
    default:
        current_led_mode = !current_led_mode;
        break;
    }
}
/*******************************************************************************
 * Защитник пробуждения *
 *******************************************************************************/
void wait_for_blue_button_release() {
    led_enable(led_all);
    LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
    LL_GPIO_InitTypeDef but_pin_init_struct;
    LL_GPIO_StructInit(&but_pin_init_struct); // значения по умолчанию
    but_pin_init_struct.Mode = LL_GPIO_MODE_INPUT;
    but_pin_init_struct.Pin = LL_GPIO_PIN_13;
    LL_GPIO_Init(GPIOC, &but_pin_init_struct);
    while (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13)) {
        led_on(led_all);
    };
    led_off(led_all);
}
/*******************************************************************************
 * Суперцикл *
 *******************************************************************************/
int main() {
    wait_for_blue_button_release();
    vterm_init(115200);
    mytimer_init(SystemCoreClock);
    led_enable(led_all);
    menu_show_title();
    MyTimer heart_rate_timer = mytimer_create(500);
    MyTimer change_led_timer = mytimer_create(500);
    MyTimer menu_timer = mytimer_create(10);
    MyTimer user_button_timer = mytimer_create(400);
    while (1) {
        // Задача Heart-Led (отрабатываем режим)
        if (mytimer_is_ready(&heart_rate_timer)) {
            hear_rate_handler(&heart_rate_timer);
        }
        // Задача смены стратегии (меняем цвет для Heart-Led)
        if (mytimer_is_ready(&change_led_timer)) {
            change_led_handler(&change_led_timer);
        }
        // Задача обработкми меню
        if (mytimer_is_ready(&menu_timer)) {
            menu_handler(&menu_timer);
        }
        if (mytimer_is_ready(&user_button_timer)) {
            led_mode_handler(&user_button_timer); // Change mode when button is pressed
        }
        // Сон (Wait for Event)
        __WFE();
    }
}