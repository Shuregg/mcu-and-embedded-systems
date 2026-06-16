#include "cm7_main.h"
#include "hal_helpers.h"

UART_HandleTypeDef huart2;

static void uart2_init(void) {
    huart2.Instance = USART2;

    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    // отключение ORE
    huart2.AdvancedInit.AdvFeatureInit =
        UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;

    huart2.AdvancedInit.OverrunDisable =
        UART_ADVFEATURE_OVERRUN_DISABLE;

    HAL_StatusTypeDef status = HAL_UART_Init(&huart2);

    if (status != HAL_OK) {
        printf("HAL_UART_Init failed: %s\r\n",
               HAL_Status_to_string(status));
        error_handler();
    }
}

void error_handler(void) {
    while (1) {
        led_toggle(led_yellow);
        HAL_Delay(100);
    }
}

int main(void) {
    HAL_Init();
    vterm_init(115200);

    // запуск ядра CM4
    HAL_RCCEx_EnableBootCore(RCC_BOOT_C2);

    // после загрузчика IRQ выключены
    __enable_irq();
    uart2_init();

    puts(u8"\r\nНажмите любую клавишу для запуска...");
    getchar();

    puts(u8"\r\nПриём хокку:\r\n");

    uint8_t ch;
    bool started = false;

    while (1) {
        HAL_StatusTypeDef status = HAL_UART_Receive(&huart2, &ch, 1, HAL_MAX_DELAY);

        if (status != HAL_OK) {
            printf("UART RX error: %s\r\n", HAL_Status_to_string(status));
            printf("UART state: %s\r\n", HAL_UART_State_to_string(HAL_UART_GetState(&huart2)));
            printf("UART err: %s\r\n", HAL_UART_Error_to_string (HAL_UART_GetError(&huart2)));
            error_handler();
        }

        // начало хокку
        if (ch == '#') {
            if (started) {
                printf("\r\n\r\n");
            }
            started = true;
        }

        if (ch == '|') {
            printf("\r\n");
            continue;
        }

        putchar(ch);
        led_toggle(RX_LED);
    }
}