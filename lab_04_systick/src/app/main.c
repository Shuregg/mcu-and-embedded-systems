/**
 * Пример планировщика на базе программных таймеров
 */
#include "user_leds.h"
#include "systim.h"
#include "mytimer.h"
#include "stm32h7xx.h"
#include "vterm.h"
#include <stdio.h>
#include "crc32.h"

#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_gpio.h"
#include "stm32h7xx_ll_iwdg.h"
#include "stm32h7xx_ll_rcc.h"

void SysTick_Handler() { systim_SysTick_Handler(); }

/*******************************************************************************
 * Программное меню *
 *******************************************************************************/

 #define NUM_COMMANDS 5
static void menu_show_tick() {
    uint32_t tick = systim_current_ms();
    if (tick) {
        printf(u8"\nВремя работы %ld.%ld секунд", tick / 1000, tick % 1000);
    } else {
        printf(u8"\nСистеменый таймер не был настроен должным образом.");
    }
};

extern const uint8_t _etext;

static void do_profile() {
    uint8_t* start_addr = (uint8_t*)0x08000000;
    uint32_t size = ((&_etext) - start_addr);

    printf("\r\n=== Profiling CRC32 ===");
    printf("\r\nSections: .isr_vector + .text");
    printf("\r\nStart: 0x%lx", (uint32_t)start_addr);
    printf("\r\nEnd:   0x%lx", (uint32_t)(&_etext));
    printf("\r\nSize: %lu byte(s)", size);

    uint32_t start_time, crc, elapsed;

    // HW 8 bit
    start_time = systim_current_ms();
    crc = calculate_CRC32_HW_8bit(start_addr, size);
    elapsed = systim_elapsed_ms(start_time);
    printf("\r\nHW8  : CRC=0x%08lX, t=%lu ms", crc, elapsed);

    // HW 32 bit
    start_time = systim_current_ms();
    crc = calculate_CRC32_HW_32bit(start_addr, size);
    elapsed = systim_elapsed_ms(start_time);
    printf("\r\nHW32 : CRC=0x%08lX, t=%lu ms", crc, elapsed);

    // SW
    start_time = systim_current_ms();
    crc = calculate_CRC32_SW(start_addr, size);
    elapsed = systim_elapsed_ms(start_time);
    printf("\r\nSW   : CRC=0x%08lX, t=%lu ms", crc, elapsed);

}

static void menu_show_title(void) {
    printf(
        u8"\r\n\n Меню приложения System clock is %ld "
        u8"MHz %s",
        SystemCoreClock / 1000000,
        u8"\n\r┌────────────┬──────────────────┬───────────┬────────────┬──────────┐"
        u8"\n\r│ 1:ShowTick │ 2: CRC Profiling │ 3:        │ 4:         │ 5: Reset │"
        u8"\n\r└────────────┴──────────────────┴───────────┴────────────┴──────────┘"
        u8"\n\r Выбор [1-6] > ");
};

typedef void (*handler_func_t)();
handler_func_t handlers[NUM_COMMANDS] = {menu_show_tick, do_profile, NULL, NULL,
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
    if(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13)) {
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

//  *******************************************************************************/
//  * Independent Watchdog Timer
//  *******************************************************************************/
void iwdg_init(void) {
    // Enable LSI clock (Low-Speed Internal)
    LL_RCC_LSI_Enable();
    while (!LL_RCC_LSI_IsReady()) {}

    // 2. Разрешить доступ к регистрам IWDG
    
    // Write 0x5555 to IWDG_KR (Unlock access to IWDG registers)
    LL_IWDG_EnableWriteAccess(IWDG1); 
    // Write 0xCCCC to IWDG_KR (start IWDT)
    LL_IWDG_Enable(IWDG1);  

    // Set prescaler (divider) coefficient
    LL_IWDG_SetPrescaler(IWDG1, LL_IWDG_PRESCALER_64);
    // Set reload value (RLR)
    LL_IWDG_SetReloadCounter(IWDG1, 499);

    while (LL_IWDG_IsReady(IWDG1) == 0U) {}

    // Update timer (write 0xAAAA to IWDG_KR)
    LL_IWDG_ReloadCounter(IWDG1);
}

void test_watchdog_hang(void) {
    printf("\r\nThis programm will suspend in 1 second...");
    systim_delay_ms(1000);
    printf("\r\nEntering the infinite loop. Please wait for reset from IWDG1...\r\n");
    while (1) {};
}


/*******************************************************************************
 * Суперцикл *
 *******************************************************************************/
int main() {
    wait_for_blue_button_release();
    vterm_init(115200);
    systim_init(SystemCoreClock);
    led_enable(led_all);
    menu_show_title();
    MyTimer heart_rate_timer = mytimer_create(500);
    MyTimer change_led_timer = mytimer_create(1000);
    MyTimer menu_timer = mytimer_create(10);
    MyTimer user_button_timer = mytimer_create(400);
    MyTimer iwdt1_feed_timer = mytimer_create(500);
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
        if(mytimer_is_ready(&iwdt1_feed_timer)) {
            mytimer_restart(&iwdt1_feed_timer);
            LL_IWDG_ReloadCounter(IWDG1);
        }

        // Сон (Wait for Event)
        __WFE();
    }
}