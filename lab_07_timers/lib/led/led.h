#pragma once

typedef enum {
    led_green = 1,
    led_yellow = 2,
    led_red = 4,
    led_all = 1|2|4
} led_t;

void led_enable(led_t led);
void led_toggle(led_t led);
void led_on(led_t led);
void led_off(led_t led);
void led_disable(led_t led);