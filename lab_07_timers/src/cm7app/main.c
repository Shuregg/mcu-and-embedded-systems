#include "main.h"
#include "boot_guard.h"


int main() {
    __enable_irq();
    boot_guard();
    vterm_init(VTERM_SPEED);
    led_enable(led_all);

    ASSERT_HAL_SATUS(HAL_Init());
    
    while (1) {
        led_toggle(led_green);
        HAL_Delay(500);
    }
    
    return 0;
}
