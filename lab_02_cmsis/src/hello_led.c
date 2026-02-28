#include <stm32h7xx.h> // основной заголовочный файл CMSIS для МК серии H7
#include <myled.h>
#include <stdio.h>
#include <vterm.h>
#include <user_leds.h>

// директива отключает оптимизацию кода компилятором для этой функции
__attribute__((optimize("-O0"))) static void delay(int ms) {
    volatile int counter = SystemCoreClock / 1000 / 6 * ms ;
    while (counter > 0) counter -= 1;
}

int main() {
    vterm_init(115200);
    led_enable(led_all);

    led_on(led_green);
    delay(500);

    led_on(led_yellow);
    delay(500);

    led_on(led_red);
    delay(500);

    while(1){
        static int counter = 0;
        printf("\r%s %d %s", "Led was toggled ", counter++, "time(s)");

        led_toggle(led_green);
        delay(500);

        led_toggle(led_yellow);
        delay(500);

        led_toggle(led_red);
        delay(500);

    };
}