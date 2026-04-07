#include <stm32h7xx.h>
#include <stdio.h>
#include <vterm.h>
#include <user_leds.h>

__attribute__((optimize("-O0"))) static void delay(int ms) {
    volatile int counter = SystemCoreClock / 1000 / 6 * ms ;
    while (counter > 0) counter -= 1;
}

int main() {
    vterm_init(115200);
    led_enable(led_yellow);
    while(1){
        static int counter = 0;
        led_toggle(led_yellow);
        printf("\r%s %d %s", "Led was toggled ", counter++, "time(s)");
        delay(500);
    };
}