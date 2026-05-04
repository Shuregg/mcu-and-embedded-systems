#include <stm32h7xx.h>
#include <systim.h>
#include <unity.h>

#define MCS_COUNT 64  // 64 МГЦ Core Clock

#pragma GCC push_options
#pragma GCC optimize("O3")

static inline void dwt_enable() {
    SET_BIT(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
}
static inline void dwt_disable() {
    CLEAR_BIT(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
}
static inline void dwt_start() {
    DWT->CYCCNT = 0;
}
static inline uint32_t dwt_get_mcs() {
    return DWT->CYCCNT / MCS_COUNT;
}

static inline void dwt_delay_mcs(int mcs) {
    uint32_t cycles = MCS_COUNT * mcs;
    DWT->CYCCNT = 0;
    while (DWT->CYCCNT < cycles)
        __asm("nop");
}
#pragma GCC pop_options


void setUp() {
    dwt_enable();
    systim_init(SystemCoreClock);
}

void tearDown() {
    dwt_disable();
}

void test_systim_current_ms() {
    uint32_t t1 = systim_current_ms();
    dwt_delay_mcs(1000);
    uint32_t t2 = systim_current_ms();
    TEST_ASSERT_EQUAL_MESSAGE(1, t2 - t1, " on 1 ms increment test");
}

void test_systim_elapsed_ms_at_once() {
    uint32_t from = systim_current_ms();
    uint32_t t2 = systim_elapsed_ms(from);
    TEST_ASSERT_EQUAL(0, t2);
}

void test_systim_elapsed_ms_some_time() {
    const uint32_t target_time = 93;
    uint32_t from = systim_current_ms();
    dwt_delay_mcs(target_time * 1000);
    uint32_t t2 = systim_elapsed_ms(from);
    TEST_ASSERT_EQUAL(target_time, t2);
}


void test_systim_delay_ms_some_time() {
    const uint32_t target_time = 13;
    uint32_t t1 = dwt_get_mcs();
    systim_delay_ms(target_time);
    uint32_t t2 = dwt_get_mcs();
    uint32_t diff = (t2 - t1) / 1000;
    // задержка не должна быть меньше, чем требовалось
    TEST_ASSERT_GREATER_OR_EQUAL(target_time, diff);
    //  ошибка должны быть меньше 2 мс
    TEST_ASSERT_LESS_THAN_UINT32(target_time + 2, diff);
}


void test_systim_delay_ms_zero_time() {
    uint32_t t1 = dwt_get_mcs();
    systim_delay_ms(0);
    uint32_t t2 = dwt_get_mcs();
    uint32_t diff = t2 > t1;
    // ожидаем, что функция вернется мгновенно с
    TEST_ASSERT_LESS_THAN_UINT32(10, diff);
}

void test_systim_delay_mcs_some_time() {
    const uint32_t target_time = 49;
    for (int i = 0; i < 5; i++) {
        uint32_t t1 = dwt_get_mcs();
        systim_delay_mcs(target_time);
        uint32_t t2 = dwt_get_mcs();
        uint32_t diff = (t2 - t1);
        // задержка не должна быть меньше, чем требовалось
        TEST_ASSERT_GREATER_OR_EQUAL(target_time, diff);
        //  погрешность не должны быть выше 50 мкс (с учетом вызовов функций тестированя)
        TEST_ASSERT_LESS_THAN_UINT32(target_time + 10 + 50, diff);
    }
}

void test_systim_delay_mcs_zero_time() {
    uint32_t t1 = dwt_get_mcs();
    systim_delay_mcs(0);
    uint32_t t2 = dwt_get_mcs();
    uint32_t diff = t2 > t1;
    // ожидаем, что функция вернется мгновенно с
    TEST_ASSERT_LESS_THAN_UINT32(10, diff);
}

void test_systim_delay_ms_huge_time() {
    dwt_delay_mcs(20000);
    systim_delay_ms(0xFFFFFFF0);
    TEST_FAIL_MESSAGE("Huge time waiting - we must not be there");
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_systim_current_ms);

    RUN_TEST(test_systim_elapsed_ms_at_once);
    RUN_TEST(test_systim_elapsed_ms_some_time);

    RUN_TEST(test_systim_delay_ms_some_time);
    RUN_TEST(test_systim_delay_ms_zero_time);

    RUN_TEST(test_systim_delay_mcs_some_time);
    RUN_TEST(test_systim_delay_mcs_zero_time);

    RUN_TEST(test_systim_delay_ms_huge_time);

    return UNITY_END();
}
