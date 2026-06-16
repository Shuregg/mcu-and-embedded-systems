/**
 * @file led.c
 * @author S.B. Simonov
 * @brief Управлеине свтеодиодами на NucleoH745
 */

#include <led.h>
#include <stm32h7xx.h>

#define TOGGLE_BIT(REG, POS) ((REG) ^= (POS))

#define led_gnpn_enable(GN, PN)                                                          \
    while (1) {                                                                          \
        SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIO##GN##EN);                                 \
        MODIFY_REG(GPIO##GN->MODER, GPIO_MODER_MODE##PN##_Msk, GPIO_MODER_MODE##PN##_0); \
        break;                                                                           \
    }

#define led_gnpn_on(GN, PN) SET_BIT(GPIO##GN->BSRR, GPIO_BSRR_BS##PN)
#define led_gnpn_off(GN, PN) SET_BIT(GPIO##GN->BSRR, GPIO_BSRR_BR##PN)
#define led_gnpn_toggle(GN, PN) TOGGLE_BIT(GPIO##GN->ODR, GPIO_ODR_OD##PN)
#define led_gnpn_disable(GN, PN) MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE##PN##_Msk, 0)

// Макросы для автоматическогой генерации функций  led_suffix
#define GNPN_CALL(SUFIX, GN, PN) led_gnpn_##SUFIX(GN, PN)
#define LED_FUNC(SUFIX)              \
    void led_##SUFIX(led_t led) {    \
        if (led & led_red) {         \
            GNPN_CALL(SUFIX, B, 14); \
        };                           \
        if (led & led_yellow) {      \
            GNPN_CALL(SUFIX, E, 1);  \
        }                            \
        if (led & led_green) {       \
            GNPN_CALL(SUFIX, B, 0);  \
        }                            \
    }

// Объявлнение функций led_suffix
LED_FUNC(enable)
LED_FUNC(toggle)
LED_FUNC(on)
LED_FUNC(off)
LED_FUNC(disable)
