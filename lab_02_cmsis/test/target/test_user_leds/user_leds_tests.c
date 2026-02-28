#include <stm32h7xx.h>
#include <user_leds.h>
#include <unity.h>

void setUp() {
    led_enable(led_all);
}

void tearDown() {
    led_disable(led_all);
    led_off(led_all);
}

void test_user_leds_toggle() {
    uint32_t odr_state_g[3] = {0};
    uint32_t odr_state_y[3] = {0};
    uint32_t odr_state_r[3] = {0};

    odr_state_g[0] = GPIOB->ODR & GPIO_ODR_OD0;
    led_toggle(led_green);
    odr_state_g[1] = GPIOB->ODR & GPIO_ODR_OD0;
    TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_g[0], odr_state_g[1],
        "Green led state not changed after toggle once");
    led_toggle(led_green);
    odr_state_g[2] = GPIOB->ODR & GPIO_ODR_OD0;
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_g[0], odr_state_g[2],
        "Green led state changed after toggle twice");

    odr_state_y[0] = GPIOE->ODR & GPIO_ODR_OD1;
    led_toggle(led_yellow);
    odr_state_y[1] = GPIOE->ODR & GPIO_ODR_OD1;
    TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_y[0], odr_state_y[1],
        "Yellow led state not changed after toggle once");
    led_toggle(led_yellow);
    odr_state_y[2] = GPIOE->ODR & GPIO_ODR_OD1;
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_y[0], odr_state_y[2],
        "Yellow led state changed after toggle twice");

    odr_state_r[0] = GPIOB->ODR & GPIO_ODR_OD14;
    led_toggle(led_red);
    odr_state_r[1] = GPIOB->ODR & GPIO_ODR_OD14;
    TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_r[0], odr_state_r[1],
        "Red led state not changed after toggle once");
    led_toggle(led_red);
    odr_state_r[2] = GPIOB->ODR & GPIO_ODR_OD14;
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_r[0], odr_state_r[2],
        "Red led state changed after toggle twice");
}

void test_user_leds_on() {
    uint32_t odr_state_g[3] = {0};
    uint32_t odr_state_y[3] = {0};
    uint32_t odr_state_r[3] = {0};

    odr_state_g[0] = GPIOB->ODR & GPIO_ODR_OD0;
    led_on(led_green);
    odr_state_g[1] = GPIOB->ODR & GPIO_ODR_OD0;
    if(!odr_state_g[0])
        TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_g[0], odr_state_g[1],
            "Green led state not changed after turning on (0 -> 0)");
    else
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_g[0], odr_state_g[1],
            "Green led state changed after turning on (1 -> 0)");

    odr_state_y[0] = GPIOE->ODR & GPIO_ODR_OD1;
    led_on(led_yellow);
    odr_state_y[1] = GPIOE->ODR & GPIO_ODR_OD1;
    if(!odr_state_y[0])
        TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_y[0], odr_state_y[1],
            "Yellow led state not changed after turning on (0 -> 0)");
    else
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_y[0], odr_state_y[1],
            "Yellow led state changed after turning on (1 -> 0)");

    odr_state_r[0] = GPIOB->ODR & GPIO_ODR_OD14;
    led_on(led_red);
    odr_state_r[1] = GPIOB->ODR & GPIO_ODR_OD14;
    if(!odr_state_r[0])
        TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_r[0], odr_state_r[1],
            "Red led state not changed after turning on (0 -> 0)");
    else
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_r[0], odr_state_r[1],
            "Red led state changed after turning on (1 -> 0)");
}

void test_user_leds_off() {
    uint32_t odr_state_g[3] = {0};
    uint32_t odr_state_y[3] = {0};
    uint32_t odr_state_r[3] = {0};

    odr_state_g[0] = GPIOB->ODR & GPIO_ODR_OD0;
    led_off(led_green);
    odr_state_g[1] = GPIOB->ODR & GPIO_ODR_OD0;
    if(!odr_state_g[0])
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_g[0], odr_state_g[1],
            "Green led state changed after turning on (0 -> 1)");
    else
        TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_g[0], odr_state_g[1],
            "Green led state not changed after turning on (1 -> 1)");

    odr_state_y[0] = GPIOE->ODR & GPIO_ODR_OD1;
    led_off(led_yellow);
    odr_state_y[1] = GPIOE->ODR & GPIO_ODR_OD1;
    if(!odr_state_y[0])
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_y[0], odr_state_y[1],
            "Yellow led state changed after turning on (0 -> 1)");
    else
        TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_y[0], odr_state_y[1],
            "Yellow led not state changed after turning on (1 -> 1)");

    odr_state_r[0] = GPIOB->ODR & GPIO_ODR_OD14;
    led_off(led_red);
    odr_state_r[1] = GPIOB->ODR & GPIO_ODR_OD14;
    if(!odr_state_r[0])
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(odr_state_r[0], odr_state_r[1],
            "Red led state not after turning on (0 -> 1)");
    else
        TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(odr_state_r[0], odr_state_r[1],
            "Red led state not changed after turning on (1 -> 1)");
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_user_leds_toggle);
    RUN_TEST(test_user_leds_on);
    RUN_TEST(test_user_leds_off);
    return UNITY_END();
}